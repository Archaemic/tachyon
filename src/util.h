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
		std::wstring name;
		unsigned width;
		std::function<std::wstring(T)> accessor;
	};

public:
	void addColumn(const std::wstring& name, std::function<std::wstring(T)> accessor, unsigned width = 0);
	void addRow(T row);
	void print() const;

private:
	std::vector<Column> m_columns;
	std::vector<T> m_rows;
};

template <typename T> void Table<T>::addColumn(const std::wstring& name, std::function<std::wstring(T)> accessor, unsigned width) {
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
	std::wcout << std::left << "|";
	for (Column column : m_columns) {
		std::wcout << " " << std::setw(column.width) << column.name << std::setw(0) << " |";
	}
	std::wcout << std::endl;
	std::wcout << "+";
	for (Column column : m_columns) {
		std::wcout << std::setw(column.width + 1) << std::setfill(L'-') << "-" << std::setw(0) << "-+";
	}
	std::wcout << std::setfill(L' ') << std::endl;
	for (const T& row : m_rows) {
		std::wcout << "|";
		for (Column column : m_columns) {
			std::wcout << " " << std::setw(column.width) << column.accessor(row) << std::setw(0) << " |";
		}
		std::wcout << std::endl;
	}
}

#endif
