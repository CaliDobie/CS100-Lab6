#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select
{
protected:
    const Spreadsheet* userSpSheet;
    int column;
    std::string userName;
public:
    Select_Contains(const Spreadsheet* sheet, const std::string& colName, const std::string& name)
    {
	column = sheet->get_column_by_name(colName);
	userName = name;
	userSpSheet = sheet;
    }
    virtual bool select(const Spreadsheet* sheet, int row) const
    {
	std::string sheetStr = sheet->cell_data(row, column);
	if(sheetStr.find(userName) != std::string::npos)
	{
	    return true;
	}
	else
	{
	    return false;
	}
    }
};

class Select_Not: public Select
{
protected:
    const Select* select1;
public:
    Select_Not(const Select* sel1)
    {
	select1 = sel1;
    }
    ~Select_Not()
    {
	delete select1;
    }
    virtual bool select(const Spreadsheet* sheet, int row) const
    {
	if(select1->select(sheet, row) == true)
	{
	    return false;
	}
	else
	{
	    return true;
	}
    }
};

class Select_And: public Select
{
protected:
    const Select* select1;
    const Select* select2;
public:
    Select_And(const Select* sel1, const Select* sel2)
    {
	select1 = sel1;
	select2 = sel2;
    }
    ~Select_And()
    {
	delete select1;
	delete select2;
    }
    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        if((select1->select(sheet, row) == true) && (select2->select(sheet, row) == true))
        {
	    return true;
        }
        else
        {
	    return false;
        }
    }
};

class Select_Or: public Select
{
protected:
    const Select* select1;
    const Select* select2;
public:
    Select_Or(const Select* sel1, const Select* sel2)
    {
	select1 = sel1;
	select2 = sel2;
    }
    ~Select_Or()
    {
	delete select1;
	delete select2;
    }
    virtual bool select(const Spreadsheet* sheet, int row) const
    {
	if((select1->select(sheet, row) == true) || (select2->select(sheet, row) == true))
	{
	    return true;
	}
	else
	{
	    return false;
	}
    }
};

#endif //__SELECT_HPP__
