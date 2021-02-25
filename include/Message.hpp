#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "utils.hpp"

class Message
{
private:
    std::string mTotalMessage;
    std::string mPrefix;
    std::string mCommand;
    std::vector<std::string> mParams;
    int mSize;

	void							skipSpace(std::string::const_iterator &iterator, const std::string &message);
	void							setString(std::string &target, std::string::const_iterator &iterator, const std::string &message);
	void							setParameters(std::string::const_iterator &iterator, const std::string &message);
	void							setVector(std::vector<std::string> &vector, std::string &parameter);
	void							setTotalMessage(const std::string &prefix, const std::string &message, const std::string &parameters);
	std::string						getParameterStr(std::string::const_iterator iterator, const std::string &message);

public:
	Message();
    Message(const std::string &preifx, const std::string &cmd, const std::string &params);
    ~Message();
	const std::string				&getPrefix(void) const;
	const std::string				&getCommand(void) const;
	const std::string				&getParameter(const int &index) const;
	const std::vector<std::string>		&getParameters(void) const;
	const std::string				&getTotalMessage(void) const;
};
#endif