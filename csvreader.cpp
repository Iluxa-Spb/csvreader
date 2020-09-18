#include "CsvHandler.h"
/// <summary>
/// into the program...
/// </summary>
/// <returns></returns>
int main(int argc, char * argv[])
{
    if (argc <= 1) {
        std::cout << "Error! The output file is not specified.";
        return 0;
    } else  if(argc > 2){
        std::cout << "Error! Too many arguments.";
        return 0;
    }
    std::string filename(argv[1]);
    CsvHandler* handler_ = new CsvHandler(filename);
    handler_->calculate_values();
    handler_->write_csv();
    handler_->write_csv_to_file("out.csv");
    return 0;
}