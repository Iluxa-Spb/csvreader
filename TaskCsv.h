#include <fstream>
/// <summary>
/// queue class for cells that need to be checked
/// </summary>
class TaskCsv
{
private:
	int x_, y_;
	std::string value_;
public:
	TaskCsv(int x, int y, std::string value);
	~TaskCsv();
	int get_x();
	int get_y();
	std::string get_value();
};