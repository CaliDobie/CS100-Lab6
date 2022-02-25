#ifndef _UNIT_TEST_HPP__
#define _UNIT_TEST_HPP__

#include "gtest/gtest.h"

#include "spreadsheet.hpp"
#include "spreadsheet.cpp"
#include "select.hpp"
#include <sstream>
#include <string>

TEST(SelectContainsTest, HeadphonesSubstring)
{
	Spreadsheet sheet;
	sheet.set_column_names({"Headphones"});
	sheet.add_row({"skullkandy"});
	sheet.add_row({"apple"});
	sheet.add_row({"bose"});
	sheet.add_row({"sony"});
	sheet.add_row({"sonys"});
	sheet.add_row({"sony_with_extrachar"});
	sheet.set_selection(new Select_Contains(&sheet, "Headphones", "sony"));
	std::stringstream ss;
	sheet.print_selection(ss);
	std::string test = ss.str();
	EXPECT_EQ(test, "sony \nsonys \nsony_with_extrachar \n")l
}

TEST(NOTTest, notS)
{
	Spreadsheet sheet;
	sheet.set_column_names({"Headphones"});
	sheet.add_row({"skullkandy"});
	sheet.add_row({"apple"});
	sheet.add_row({"bose"});
	sheet.add_row({"sony"});
	sheet.set_seleciton(new Select_Not(new Select_Contains(&sheet, "Headphones","a")));
	std:stringstream ss;
	sheet.print_selection(ss);
	std::string test == ss.str();
	EXPECT_EQ(test, "sony \nbose \n");
}

TEST(ANDTest, OandS)
{
	Spreadsheet sheet;
	sheet.set_column_names({"Headhpones"});
	sheet.add_row({"skullkandy"});
	sheet.add_row({"apple"});
	sheet.add_row({"sony"});
	sheet.add_row({"bose"});
	sheet.set_selection(new Select_And(new Select_Contains(&sheet, "Headphones", "o"), new Select_Contains(&sheet, "Headphones", "s")));
	std::stringstream ss;
	sheet.print_selection(ss);
	std::string test = ss.str();
	EXPECT_EQ(test, "sony \nbose \n");
}

TEST(ORTest, KorA)
{
	Spreadsheet sheet;
	sheet.set_column_names({"Headphones"});
	sheet.add_row({"skullkandy"});
	sheet.add_row({"apple"});
	sheet.add_row({"sony"});
	sheet.add_row({"bose"});
	sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "Headphones", "k"), new Select_Contains(&sheet, "Headhpones", "a")));
	std::stringstream ss;
	sheet.print_selection(ss);
	std::string test = ss.str();
	EXPECT_EQ(test, "skullkandy \napple \n");
}

#endif //__UNIT_TEST_HPP_	
