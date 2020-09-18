#include <fstream>
#include <vector>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <iostream>
#include <algorithm>
#include <queue> 
#include "TaskCsv.h"
#include <string>


/// <summary>
/// class for working with csv files
/// </summary>
class CsvHandler
{
private:
	/// <summary>
	/// array with header data
	/// </summary>
	std::vector<std::string> headerLine_;
	/// <summary>
	/// array with number line data
	/// </summary>
	std::vector<std::string> numberLine_;
	/// <summary>
	/// main array data
	/// </summary>
	std::vector < std::vector < std::string >> csvList_;
	/// <summary>
	/// array of tasks
	/// </summary>
	std::queue <TaskCsv> taskQueue_;

	template < typename Type > std::string to_str(const Type& t);
	bool is_digit(const std::string& s);
	bool is_letter(const std::string& s);
public:
	CsvHandler();
	CsvHandler(std::string filename);
	~CsvHandler();
	void read_csv(std::string filename);
	void write_csv();
	void write_csv_to_file(std::string filename);
	std::string check_cell(const int& x, const int& y, const std::string& value);
	bool check_recursion(const int& x, const int& y);
	int get_cell_x_to_int(const std::string& x);
	int get_cell_y_to_int(const std::string& y);
	std::string get_cell(const std::string& x, const std::string& y);
	std::string get_cell(const int& x, const int& y);
	void set_cell(const int& x, const int& y, const std::string value);
	void calculate_values();
};