#ifndef __UNIT_TEST_HPP__
#define __UNIT_TEST_HPP__

#include "gtest/gtest.h"

#include "spreadsheet.hpp"
#include "spreadsheet.cpp"
#include "select.hpp"
#include <sstream>
#include <string>

TEST(SelectContainsTest, AppleSubstring)
{
    Spreadsheet sheet;
    sheet.set_column_names({"Food"});
    sheet.add_row({"app"});
    sheet.add_row({"apple"});
    sheet.add_row({"apples"});
    sheet.add_row({"snapple"});
    sheet.set_selection(new Select_Contains(&sheet, "Food", "apple"));
    std::stringstream ss;
    sheet.print_selection(ss);
    std::string test = ss.str();
    EXPECT_EQ(test, "apple \napples \nsnapple \n");
}

TEST(NOTTest, notS)
{
    Spreadsheet sheet;
    sheet.set_column_names({"Food"});
    sheet.add_row({"app"});
    sheet.add_row({"apple"});
    sheet.add_row({"apples"});
    sheet.add_row({"snapple"});
    sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Food", "s")));
    std::stringstream ss;
    sheet.print_selection(ss);
    std::string test = ss.str();
    EXPECT_EQ(test, "app \napple \n");
}

TEST(ANDTest, IandE)
{
    Spreadsheet sheet;
    sheet.set_column_names({"Food"});
    sheet.add_row({"pie"});
    sheet.add_row({"apple"});
    sheet.add_row({"fries"});
    sheet.add_row({"pizza"});
    sheet.set_selection(new Select_And(new Select_Contains(&sheet, "Food", "i"), new Select_Contains(&sheet, "Food", "e")));
    std::stringstream ss;
    sheet.print_selection(ss);
    std::string test = ss.str();
    EXPECT_EQ(test, "pie \nfries \n");
}

TEST(ORTest, IorE)
{
    Spreadsheet sheet;
    sheet.set_column_names({"Food"});
    sheet.add_row({"pie"});
    sheet.add_row({"apple"});
    sheet.add_row({"fries"});
    sheet.add_row({"pizza"});
    sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "Food", "i"), new Select_Contains(&sheet, "Food", "e")));
    std::stringstream ss;
    sheet.print_selection(ss);
    std::string test = ss.str();
    EXPECT_EQ(test, "pie \napple \nfries \npizza \n");
}

#endif //__UNIT_TEST_HPP__
