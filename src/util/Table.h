#ifndef PTXN_UTIL_H
#define PTXN_UTIL_H

#include <functional>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

template <typename T>
class Table {
private:
	struct Column {
		std::string name;
		unsigned width;
		std::function<std::string(T)> accessor;
	};

public:
	void addColumn(const std::string& name, std::function<std::string(T)> accessor, unsigned width = 0);
	void addRow(T row);
	void print() const;

private:
	std::vector<Column> m_columns;
	std::vector<T> m_rows;
};

template <typename T> void Table<T>::addColumn(const std::string& name, std::function<std::string(T)> accessor, unsigned width) {
	Column column = {
		.name = name,
		.width = width,
		.accessor = accessor
	};
	m_columns.push_back(column);
}

template <typename T> void Table<T>::addRow(T row) {
	m_rows.push_back(row);
}

template <typename T> void Table<T>::print() const {
	std::cout << std::left << "|";
	for (Column column : m_columns) {
		std::cout << " " << std::setw(column.width) << column.name << std::setw(0) << " |";
	}
	std::cout << std::endl;
	std::cout << "+";
	for (Column column : m_columns) {
		std::cout << std::setw(column.width + 1) << std::setfill('-') << "-" << std::setw(0) << "-+";
	}
	std::cout << std::setfill(' ') << std::endl;
	for (const T& row : m_rows) {
		std::cout << "|";
		for (Column column : m_columns) {
			std::cout << " " << std::setw(column.width) << column.accessor(row) << std::setw(0) << " |";
		}
		std::cout << std::endl;
	}
}

#endif
