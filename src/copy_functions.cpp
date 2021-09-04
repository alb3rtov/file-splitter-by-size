#ifndef _COPY_FUNCTIONS_
#define _COPY_FUNCTIONS_

#include <iostream>
#include <string>
#include <regex>
#include <sys/stat.h>
#include <filesystem>
#include <math.h>
#include <limits>
#include <chrono>

#include "..\include\definitions.hpp"

std::string drive_letter;
std::string directory_path;
bool first_time = true;

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
            total_size = total_size + std::filesystem::file_size(path);
        }
    }

    return total_size;
}

/* Generate current vector with files */
long long int generate_current_vector_files(std::vector<std::string> &current_files, std::vector<std::string> &files,
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

    return total_files_sizes;
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

/* Convert long long int bytes to double gigabytes */
double convert_to_gb_from_long_int(long long int size)
{
    double kb_size = size / 1024;
    double mb_size = kb_size / 1024;
    double gb_size = mb_size / 1024;

    return gb_size;
}

double convert_to_mb_from_long_int(long long int size)
{
    double kb_size = size / 1024;
    double mb_size = kb_size / 1024;

    return mb_size;
}

/* Add space characters to avoid output overwrite */
std::string add_space_characters(int index, std::vector<std::string> current_files, int current_file_length)
{

    int previous_file_length = current_files.at(index - 1).length();
    int diff = previous_file_length - current_file_length;

    std::string str = "";

    if (diff > 0) /* Only add spaces characters if previous file path is larger than the current file path */
    {
        for (int i = 0; i < diff; i++) /* Add the diff number spaces characters */
        {
            str.append(" ");
        }
    }

    return str;
}

/* Generate a percentage of the current copy process */
void generate_dynamic_percentage(long long gb_size, long long int current_filesize, double &percentage,
                                 std::string new_path_file, bool &first_output, std::vector<std::string> current_files, int index)
{
    percentage = percentage + (convert_to_gb_from_long_int(current_filesize) * 100) / (convert_to_gb_from_long_int(gb_size));

    if (first_output)
    {
        first_output = false;
        std::cout << "Progress: " << std::fixed << std::setprecision(2) << percentage << " %" << std::endl;
        std::cout << "Copying file " << new_path_file << "... (" << index << "/" << current_files.size() - 1 << ")" << std::endl;
    }
    else
    {
        std::cout << "\033[FCopying file " << new_path_file << "... (" << index << "/" << current_files.size() - 1 << ")" << add_space_characters(index, current_files, new_path_file.length());
        std::cout << "\033[FProgress: " << std::fixed << std::setprecision(2) << percentage << " %\n\n";
    }
}

/* Perform the copy of current files on the vector */
std::chrono::duration<double> copy_files(std::vector<std::string> current_files, std::vector<long long int> files_sizes_aux, int num, long long int gb_size, int &index)
{
    double percentage = 0;
    bool first_output = true;

    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < current_files.size(); i++)
    {
        std::string new_path_file = generate_path_file_backup(current_files.at(i), num);
        generate_dynamic_percentage(gb_size, files_sizes_aux.at(index), percentage, new_path_file, first_output, current_files, i);

        if (!CopyFileA(current_files.at(i).c_str(), new_path_file.c_str(), 0))
        {
            std::cout << "Error: " << GetLastError() << std::endl;
        }
        index++;
    }
    std::cout << "\n";

    auto end = std::chrono::system_clock::now();

    return end - start;
}

/* Convert elapsed time to minutes if is necessary */
void get_elapsed_time(double elapsed_time)
{

    if (elapsed_time > 60)
    {
        int minutes = elapsed_time / 60;
        double d_minutes = elapsed_time / 60;
        int seconds = (d_minutes - minutes) * 60;
        std::cout << "Elapsed time: " << minutes << " minutes " << seconds << " seconds. ";
    }
    else
    {
        std::cout << "Elapsed time: " << elapsed_time << " seconds. ";
    }
}

/* Print information about copy process */
void pause(double gb_size, long long current_size, bool flag, std::chrono::duration<double> elapsed)
{
    std::cout << "The copy process is finished." << std::endl;
    std::cout << convert_to_gb_from_long_int(current_size) << " of " << gb_size << " GB has been copied" << std::endl;
    std::cout << "Now, you can extract the drive " + drive_letter << std::endl;

    if (flag)
    {
        std::cout << "All copies have been completed successfully" << std::endl;
        get_elapsed_time(elapsed.count());
        std::cout << "Write speed: " << std::fixed << std::setprecision(2) << convert_to_mb_from_long_int(current_size) / elapsed.count() << " MB/s" << std::endl;
        std::cout << "\nPress enter to exit";
    }
    else
    {
        std::cout << "Before continue copying the next files, make sure you have delete the previous copy" << std::endl;
        get_elapsed_time(elapsed.count());
        std::cout << "Write speed: " << std::fixed << std::setprecision(2) << convert_to_mb_from_long_int(current_size) / elapsed.count() << " MB/s" << std::endl;
        std::cout << "\nPress enter to continue";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/* Main function to make copy */
void make_copy()
{
    long long int size = 0;
    ULARGE_INTEGER total_number_of_free_bytes = {0};

    std::vector<std::string> files;
    std::vector<std::string> directories;
    std::vector<long long int> files_sizes;
    std::vector<long long int> files_sizes_aux;

    if (!drive_letter.empty() && !directory_path.empty())
    {
        size = list_all_files(directory_path, files, files_sizes, directories);

        for (int i = 0; i < files_sizes.size(); i++)
        {
            files_sizes_aux.push_back(files_sizes.at(i));
        }

        double gb_size = convert_to_gb_from_long_int(size);
        std::cout << "\nTotal size of copy: " << std::fixed << std::setprecision(2) << gb_size << " GB\n"
                  << std::endl;

        GetDiskFreeSpaceExA(drive_letter.c_str(), NULL, NULL, &total_number_of_free_bytes);
        double gb_drive = convert_to_gigabytes(total_number_of_free_bytes);
        int num = get_num_real_directory(directory_path);

        int index = 0;
        long long int total_size = 0;
        bool end = false;
        bool flag = false;

        if (first_time)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            first_time = false;
        }

        std::cout << "Press enter to start the copy process..." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while (!end)
        {
            std::vector<std::string> current_files;
            long long int current_size = generate_current_vector_files(current_files, files, files_sizes, total_number_of_free_bytes.QuadPart);

            if (current_size <= total_number_of_free_bytes.QuadPart) /* Check if there is enough space in the drive */ 
            {
                total_size = total_size + current_size;
                generate_directories_structure(num, directories);
                std::chrono::duration<double> elapsed = copy_files(current_files, files_sizes_aux, num, total_size, index);

                if (total_size >= size)
                {
                    end = true;
                    flag = true;
                }

                pause(gb_size, total_size, flag, elapsed);
            } 
            else 
            {
                std::cout << "There is not enough space (" << gb_drive << " GB free) for make the copy (" 
                            << convert_to_gb_from_long_int(current_size) << " GB)";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');       
            }
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