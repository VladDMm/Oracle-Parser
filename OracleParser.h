#pragma once
#include <vector>
#include <string>

enum class StmtType { SQL, PLSQL };

struct OracleStmt
{
	std::string text;
	StmtType type;
};

class OracleParser
{
private:
	std::string input;
	std::vector<OracleStmt> out;

	void formatStmt();

	std::string trim(std::string s);

	bool is_plsql_start(const std::string& s);

	bool StartWithCh(const std::string& s, const std::string& p);

public:
	OracleParser(std::string& stmt) : input(stmt)
	{
		formatStmt();
	}
	OracleParser(const char* stmt) : input(stmt)
	{
		formatStmt();
	}

	std::vector<OracleStmt> SplitOracleStatement();
};

