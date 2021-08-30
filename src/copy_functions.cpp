#ifndef _COPY_FUNCTIONS_
#define _COPY_FUNCTIONS_

#include <iostream>
#include <string>
#include <regex>
#include <sys/stat.h>
#include <filesystem>
#include <math.h>

#include "..\include\definitions.hpp"

std::string drive_letter;
std::string directory_path;

/* Check all attributes values to print if contain smth */
void check_current_attrs_values()
{
    std::cout << "\n\n\n\n\n\n\n"
              << std::endl;

    if (!drive_letter.empty())
    {
        std::cout << BHIYELLOW << "\nCurrent selected drive letter: " << drive_letter;
    }

    if (!directory_path.empty())
    {
        std::cout << BHIYELLOW << "\nCurrent selected directory path: " << directory_path;
    }
}

/* Returns bool that indicates if a given path exists */
bool is_path_exist(const std::string &s)
{
    struct stat buffer;
    return (stat(s.c_str(), &buffer) == 0);
}

/* Request drive letter to user */
void select_drive_letter()
{
    do
    {
        std::cout << "\nSelect drive letter (e.g.: E): ";
        std::cin >> drive_letter;
    } while (!std::regex_match(drive_letter, std::regex("[A-Za-z]")) && (drive_letter.size() != 1));
    drive_letter.append(":\\");
    drive_letter.append("\\");

    clear_display_banner_and_menu();
    check_current_attrs_values();
}

/* Request directory where make the backup to user */
void select_directory()
{
    do
    {
        std::cout << "\nSelect directory (i.e.: D:\\Data ): ";
        std::cin >> directory_path;
    } while (!is_path_exist(directory_path));

    clear_display_banner_and_menu();
    check_current_attrs_values();
}

/* List all files in directory and sub-directories */
long long int list_all_files(std::string directory_path, std::vector<std::string> &files,
                             std::vector<long long int> &files_sizes, std::vector<std::string> &directories)
{
    long long int total_size = 0;
    std::string path;

    for (const auto &entry : std::filesystem::directory_iterator(directory_path))
    {
        path = entry.path().string();

        if (std::filesystem::is_directory(path))
        {
            directories.push_back(path);
            total_size = total_size + list_all_files(path, files, files_sizes, directories);
        }
        else
        {
            files.push_back(path);
            files_sizes.push_back(std::filesystem::file_size(path));
            //std::cout << path << "  " << std::filesystem::file_size(path) << std::endl;
            total_size = total_size + std::filesystem::file_size(path);
        }
    }

    return total_size;
}

/* Generate current vector with files */
void generate_current_vector_files(std::vector<std::string> &current_files, std::vector<std::string> &files,
                                   std::vector<long long int> &files_sizes, long long int total_number_of_free_bytes)
{
    long long int total_files_sizes = 0;

    while (!files.empty())
    {

        std::string current_file = files.at(0);
        long long current_size = files_sizes.at(0);
        total_files_sizes = total_files_sizes + current_size;

        if (total_files_sizes >= total_number_of_free_bytes)
        {
            total_files_sizes = total_files_sizes - current_size;
            break;
        }
        else
        {
            files.erase(files.begin());
            files_sizes.erase(files_sizes.begin());
            current_files.push_back(current_file);
        }
    }
}

/* Get number where last backslash of the path is */
int get_num_real_directory(std::string directory_path)
{
    int i = 0;
    for (i = directory_path.size() - 1; i >= 0; i--)
    {
        if (directory_path[i] == '\\')
        {
            break;
        }
    }
    return i;
}

/* Generate the directory structure on USB drive selected */
void generate_directories_structure(int num, std::vector<std::string> directories)
{
    std::string main_path = drive_letter.substr(0, 2).append(directory_path.substr(num, directory_path.size() - 1));

    if (!CreateDirectoryA(main_path.c_str(), 0))
    {
        if (GetLastError() != ERROR_ALREADY_EXISTS)
        {
            std::cout << "Error: " << GetLastError() << std::endl;
        }
    }

    for (int i = 0; i < directories.size(); i++)
    {
        std::string new_path = drive_letter.substr(0, 2).append(directories.at(i).substr(num, directories.at(i).size() - 1));
        if (!CreateDirectoryA(new_path.c_str(), 0))
        {
            if (GetLastError() != ERROR_ALREADY_EXISTS)
            {
                std::cout << "Error: " << GetLastError() << std::endl;
            }
        }
    }
}

/* Generate the new path for files on USB drive */
std::string generate_path_file_backup(std::string current_path, int num)
{
    std::string new_path = drive_letter.substr(0, 2).append(current_path.substr(num, current_path.size() - 1));
    return new_path;
}

/* Generate a percentage of the current copy process */
void generate_dynamic_percentage(double gb_size, long long int current_filesize, double &percentage)
{
    double kb_current_file_size = current_filesize / 1024;
    double mb_current_file_size = kb_current_file_size / 1024;
    double gb_current_file_size = mb_current_file_size / 1024;

    percentage = percentage + (gb_current_file_size*100)/gb_size;
    std::cout << "Progress: " << std::fixed << std::setprecision(2) << percentage << " %\r";
}

/* Perform the copy of current files on the vector */
void copy_files(std::vector<std::string> current_files, std::vector<long long int> files_sizes_aux, int num, double gb_size, int &index)
{
    double percentage = 0;

    for (int i = 0; i < current_files.size(); i++)
    {
        std::string new_path_file = generate_path_file_backup(current_files.at(i), num);

        //GENERATE PROGRESS BAR AND SHOW WHAT FILES HAVE BEEN COPIED
        //std::cout << "Copying file " << new_path_file << " - ";
        generate_dynamic_percentage(gb_size, files_sizes_aux.at(index), percentage);
        
        if (!CopyFileA(current_files.at(i).c_str(), new_path_file.c_str(), 0))
        {
            std::cout << "Error: " << GetLastError() << std::endl;
        }
        index++;
    }
}

/* Main function to make copy */
void make_copy()
{
    long long int size = 0;
    int iterations = 0;
    ULARGE_INTEGER total_number_of_free_bytes = {0};
    std::vector<std::string> files;
    std::vector<std::string> directories;
    std::vector<long long int> files_sizes;
    std::vector<long long int> files_sizes_aux;

    if (!drive_letter.empty() && !directory_path.empty())
    {
        size = list_all_files(directory_path, files, files_sizes, directories);

        for (int i = 0; i < files_sizes.size(); i++) {
            files_sizes_aux.push_back(files_sizes.at(i));
        }

        double kb_size = size / 1024;
        double mb_size = kb_size / 1024;
        double gb_size = mb_size / 1024;
        std::cout << "\nTotal size: " << std::fixed << std::setprecision(2) << gb_size << " GB" << std::endl;

        GetDiskFreeSpaceExA(drive_letter.c_str(), NULL, NULL, &total_number_of_free_bytes);
        double gb_drive = convert_to_gigabytes(total_number_of_free_bytes);
        double num_division = gb_size / gb_drive;

        iterations = (num_division <= 1) ? 1 : ceil(num_division);

        int num = get_num_real_directory(directory_path);
        //std::cout << iterations << std::endl;
        int index = 0;
        for (int i = 0; i < iterations; i++)
        {
            std::vector<std::string> current_files;
            generate_current_vector_files(current_files, files, files_sizes, total_number_of_free_bytes.QuadPart);
            generate_directories_structure(num, directories);
            copy_files(current_files, files_sizes_aux, num, gb_size, index);
        }
    }
    else
    {
        std::cout << BHIRED << "\nYou need to select a drive letter, a directory and a maximum space." << std::endl;
    }

    clear_display_banner_and_menu();
    check_current_attrs_values();
}

#endif