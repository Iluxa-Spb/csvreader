#include "TaskCsv.h"

TaskCsv::TaskCsv(int x, int y, std::string value) {
	x_ = x;
	y_ = y;
	value_ = value;
}
TaskCsv::~TaskCsv() {
	x_ = 0;
	y_ = 0;
	value_ = "";
}
int TaskCsv::get_x() {
	return x_;
}
int TaskCsv::get_y() {
	return y_;
}
std::string TaskCsv::get_value() {
	return value_;
}