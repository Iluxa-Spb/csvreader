#include "CsvHandler.h"

/// <summary>
/// empty constructor
/// </summary>
CsvHandler::CsvHandler() {

}
/// <summary>
/// constructor that accepts filename
/// </summary>
/// <param name="filename">filename loaded resources</param>
CsvHandler::CsvHandler(std::string filename) {
    read_csv(filename);
}
/// <summary>
/// destructor
/// </summary>
CsvHandler::~CsvHandler() {
}
/// <summary>
/// reading data from file
/// </summary>
/// <param name="filename">filename loaded resources</param>
void CsvHandler::read_csv(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) throw std::runtime_error("Could not open file with filename:"+filename);

    csvList_.push_back(std::vector <std::string>());
    numberLine_.push_back("");
    int count_y = 0;
    std::string line;
    std::string colname;

    // Read the column names
    if (file.good())
    {
        // Extract the first line in the file
        std::getline(file, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while (std::getline(ss, colname, ',')) {
            //Initialize and add colname in header line and csv list
            if (is_letter(colname) || colname == "")
            {
                headerLine_.push_back(colname);
                csvList_.at(count_y).push_back(colname);
            }
        }
    }

    // Read data, line by line
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        csvList_.push_back(std::vector <std::string>());
        count_y++;
        int count_x = 0;

        while (std::getline(ss, colname, ',')) {
            csvList_.at(count_y).push_back(colname);
            if (!is_digit(colname)) {
                taskQueue_.push(TaskCsv(count_x, count_y, colname));
            }
            count_x++;
        }
        numberLine_.push_back(csvList_.at(count_y).at(0));

    }
    file.close();
}
/// <summary>
/// displaying data on the screen
/// </summary>
void CsvHandler::write_csv() {
    for (int i = 0; i < csvList_.size(); ++i)
    {
        for (int j = 0; j < csvList_.at(i).size(); ++j) {
            std::cout << csvList_.at(i).at(j);
            if (j < csvList_.at(i).size() - 1) std::cout << ",";
        }
        std::cout << "\n";
    }
}
/// <summary>
/// output data to file
/// </summary>
/// <param name="filename">name file to write data</param>
void CsvHandler::write_csv_to_file(std::string filename) {
    std::ofstream file(filename);

    for (int i = 0; i < csvList_.size(); ++i)
    {
        for (int j = 0; j < csvList_.at(i).size(); ++j) {
            file << csvList_.at(i).at(j);
            if (j < csvList_.at(i).size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}
/// <summary>
/// to edit the float output
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <param name="t">editable float</param>
/// <returns>edited float</returns>
template < typename Type > std::string CsvHandler::to_str(const Type& t)
{
    std::ostringstream os;
    os << t;
    return os.str();
}
/// <summary>
/// check is a string number
/// </summary>
/// <param name="s">input string</param>
/// <returns>answer true/false</returns>
bool CsvHandler::is_digit(const std::string& s)
{
    return !s.empty() && (s.find_first_not_of("0123456789-.") == s.npos);
}
/// <summary>
/// is a string Latin letters
/// </summary>
/// <param name="s">input string</param>
/// <returns>answer true/false</returns>
bool CsvHandler::is_letter(const std::string& s)
{
    return !s.empty() && (s.find_first_not_of(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == s.npos);
}
/// <summary>
/// the main function of the test cell
/// first: it separates elements
/// second: checks for exceptions
/// third: if need, starts recursion the function
/// fourth: performs calculations of values
/// </summary>
/// <param name="x">x function being checked</param>
/// <param name="y">y function being checked</param>
/// <param name="value">cell value</param>
/// <returns>result of computation</returns>
std::string CsvHandler::check_cell(const int& x, const int& y, const std::string& value) {
    if (is_digit(value)) return value;

    std::vector<std::string> hl;
    std::vector<char> sl;
    std::vector<std::string> nl;

    std::string temp = "";

    bool isDigit = false;
    bool isChar = false;
    bool isString = false;

    int count = 0;

    if (value.at(0) == '=') {
        for (std::string::size_type i = 1; i < value.size(); ++i) {
            if (isString) {
                if (!std::isalpha((unsigned char)value[i])) {
                    hl.push_back(temp);
                    isString = false;
                    temp = "";
                }
            }
            else if (isDigit) {
                if (!std::isdigit((unsigned char)value[i])) {
                    nl.push_back(temp);
                    isDigit = false;
                    temp = "";
                }
            }
            else if (isChar) {
                isChar = false;
                temp = "";
            }

            if (std::isalpha((unsigned char)value[i]))
            {
                isString = true;
                temp += value[i];
            }
            else if (std::isdigit((unsigned char)value[i]))
            {
                isDigit = true;
                temp += value[i];
                if (i == value.size() - 1)
                {
                    nl.push_back(temp);
                    isDigit = false;
                    temp = "";
                }
            }
            else if (value[i] == '+' ||
                value[i] == '-' ||
                value[i] == '/' ||
                value[i] == '*')
            {
                isChar = true;
                sl.push_back(value[i]);
            }
            else return "WS"; //wrong sign
        }

        if (hl.size() == nl.size())
        {
            std::vector<float> values;
            float result;
            for (int i = 0; i < hl.size(); i++)
            {
                int xt = get_cell_x_to_int(hl.at(i));
                if (xt == 0) return "EH"; //error header
                int yt = get_cell_y_to_int(nl.at(i));
                if (yt == 0) return "EN"; //error number
                if (y == yt && x == xt) return "RR"; //recursion error
                std::string val = get_cell(xt, yt);
                if (!is_digit(val))
                {
                    int pos = val.find(headerLine_.at(xt) + numberLine_.at(yt));
                    if (pos != 0) return "RR"; //recursive error
                    set_cell(xt, yt, check_cell(xt, yt, val));
                }
                if (is_digit(get_cell(xt, yt))) values.push_back(stof(get_cell(xt, yt)));
                else return "WC";

            }
            result = values.at(0);
            for (int i = 0; i < sl.size(); i++)
            {
                switch (sl.at(i))
                {
                case '+':
                    result += values.at(i + 1);
                    break;
                case '-':
                    result -= values.at(i + 1);
                    break;
                case '*':
                    result *= values.at(i + 1);
                    break;
                case '/':
                    result /= values.at(i + 1);
                    break;
                default:
                    break;
                }
            }
            //return std::to_string(result);
            return to_str(result);
        }
        else
            return "WC"; //wrong condition
    }
    else
    {
        return "WC"; //wrong condition
    }

    return "";
}

/// <summary>
/// find header index
/// </summary>
/// <param name="x">string header line name</param>
/// <returns>index header line</returns>
int CsvHandler::get_cell_x_to_int(const std::string& x) {
    int i;
    std::vector < std::string > ::iterator ih = std::find(headerLine_.begin(), headerLine_.end(), x);
    if (ih != headerLine_.end()) {
        i = std::distance(headerLine_.begin(), ih);
        return i;
    }
    else
        return 0; //error compile header line
}
/// <summary>
/// find number index
/// </summary>
/// <param name="y">string digit line name</param>
/// <returns>index digit line</returns>
int CsvHandler::get_cell_y_to_int(const std::string& y) {
    int i;
    std::vector < std::string > ::iterator in = std::find(numberLine_.begin(), numberLine_.end(), y);
    if (in != numberLine_.end()) {
        i = std::distance(numberLine_.begin(), in);
        return i;
    }
    else
        return 0; //error compile number line
}
/// <summary>
/// get cell input string param
/// </summary>
/// <param name="x">string x param</param>
/// <param name="y">string y param</param>
/// <returns>string value cell</returns>
std::string CsvHandler::get_cell(const std::string& x, const std::string& y) {
    int inum, ihead;
    //find header index
    ihead = get_cell_x_to_int(x);
    if (ihead == 0) return "EH"; //error compile header line
    inum = get_cell_y_to_int(y);
    if (inum == 0) return "EN"; //error compile number line

    return csvList_.at(inum).at(ihead);
}
/// <summary>
/// get cell input int param
/// </summary>
/// <param name="x">int x index</param>
/// <param name="y">int y index</param>
/// <returns>string value cell</returns>
std::string CsvHandler::get_cell(const int& x, const int& y) {
    return csvList_.at(y).at(x);
}
/// <summary>
/// set value cell
/// </summary>
/// <param name="x">int x index</param>
/// <param name="y">int y index</param>
/// <param name="value">string change value</param>
void CsvHandler::set_cell(const int& x, const int& y, const std::string value) {
    csvList_.at(y).at(x) = value;
}
/// <summary>
/// converting CSV table
/// </summary>
void CsvHandler::calculate_values() {
    while (!taskQueue_.empty())
    {
        if (is_digit(get_cell(taskQueue_.front().get_x(), taskQueue_.front().get_y()))
            || get_cell(taskQueue_.front().get_x(), taskQueue_.front().get_y()) == "WC" //wrong condition
            || get_cell(taskQueue_.front().get_x(), taskQueue_.front().get_y()) == "WS" //wrong sign
            || get_cell(taskQueue_.front().get_x(), taskQueue_.front().get_y()) == "RR" //recursion error
            || get_cell(taskQueue_.front().get_x(), taskQueue_.front().get_y()) == "EH" //header error - header not found
            || get_cell(taskQueue_.front().get_x(), taskQueue_.front().get_y()) == "EN") { //number error - number line not found
            taskQueue_.pop();
        }
        else {
            set_cell(taskQueue_.front().get_x(),
                taskQueue_.front().get_y(),
                check_cell(taskQueue_.front().get_x(), taskQueue_.front().get_y(), taskQueue_.front().get_value()));
        }
    }
}