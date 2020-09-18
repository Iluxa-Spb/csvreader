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
    } else  if(argc > 3){
        std::cout << "Error! Too many arguments.";
        return 1;
    }
    std::string infilename(argv[1]);
    std::string outfilename;
    CsvHandler* handler_ = new CsvHandler(infilename);
    handler_->calculate_values();
    handler_->write_csv();
    if (argc == 2){
        outfilename = argv[2];
        handler_->write_csv_to_file(outfilename);
    }
    else
        handler_->write_csv_to_file("out.csv");
    return 0;
}