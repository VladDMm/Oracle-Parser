#include "OracleParser.h"

void OracleParser::formatStmt()
{
	std::string::size_type lenght = input.size();
	char* dest = new char[lenght + 1];
	std::string::size_type i = 0, j = 0;

	while (i < lenght)
	{
		while (i + 1 < lenght && (input[i] == ' ' || input[i] == '\t') && isspace((unsigned char)input[i + 1]))
			++i;

		if (input[i] == '\"')
			dest[j++] = '\'';
		else
			dest[j++] = input[i];

		++i;
	}

	input.assign(dest, j);
	input = trim(input);

	delete[] dest;
}

std::string OracleParser::trim(std::string s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [this](char ch)
		{ return !isspace((unsigned char)ch); }));

	s.erase(std::find_if(s.rbegin(), s.rend(), [this](char ch)
		{ return !isspace((unsigned char)ch); }).base(), s.end());

	return s;
}

bool OracleParser::is_plsql_start(const std::string& s)
{
	// CREATE [OR REPLACE] TRIGGER
	// CREATE [OR REPLACE] PROCEDURE
	// CREATE [OR REPLACE] FUNCTION
	// DECLARE
	// CREATE PACKAGE
	// BEGIN
	std::string u = s;
	for (char& c : u) c = toupper((unsigned char)c);

	if (StartWithCh(u, "DECLARE"))
		return true;
	if (StartWithCh(u, "BEGIN"))
		return true;

	if (StartWithCh(u, "CREATE") &&
		u.find("TRIGGER") != std::string::npos ||
		u.find("PROCEDURE") != std::string::npos ||
		u.find("FUNCTION") != std::string::npos ||
		u.find("PACKAGE") != std::string::npos)
		return true;

	return false;
}

bool OracleParser::StartWithCh(const std::string& s, const std::string& p)
{
	if (s.size() < p.size())
		return false;

	for (size_t i = 0; i < p.size(); ++i)
		if (toupper(s[i]) != toupper(p[i])) return false;

	return true;
}

std::vector<OracleStmt> OracleParser::SplitOracleStatement()
{
	char ch = ' ';
	bool isPlSQL = false;
	std::string buff{};

	for (std::string::size_type i = 0; i < input.size(); ++i)
	{
		ch = input[i];

		if (ch == ';' && isPlSQL == false)
		{
			if (!is_plsql_start(trim(buff)))
			{
				out.push_back(OracleStmt{
				trim(buff),
				isPlSQL ? StmtType::PLSQL : StmtType::SQL });
				buff.clear();
				isPlSQL = false;
				continue;
			}
			isPlSQL = true;
		}
		if (ch == '/' && isPlSQL)
		{
			out.push_back(OracleStmt{
				trim(buff),
				isPlSQL ? StmtType::PLSQL : StmtType::SQL
				});
			buff.clear();
			isPlSQL = false;
			continue;
		}

		buff += ch;
	}
	// daca o fost scapat la final ";" pentru stmt sau "/" pentru plsql
	if (!buff.empty())
		out.push_back(OracleStmt{
				trim(buff),
				isPlSQL ? StmtType::PLSQL : StmtType::SQL
			});

	return out;
}