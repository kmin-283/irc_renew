#include "Message.hpp"

Message::Message()
{}

Message::Message(const std::string &err)
	: mPrefix(""), mCommand(err)
{
	std::string tmpParameters = CR_LF;

	this->setTotalMessage(mPrefix, mCommand, tmpParameters);
	this->mSize = this->mTotalMessage.length();
}

Message::Message(const std::string &prefix, const std::string &command, const std::string &parameters)
	: mPrefix(prefix), mCommand(command)
{
	std::string tmpParameters;
	std::string::const_iterator iterator;


	std::transform(mCommand.begin(), mCommand.end(), mCommand.begin(), toupper);
	tmpParameters = parameters;
	tmpParameters += CR_LF;
	iterator = tmpParameters.begin();
	this->setTotalMessage(prefix, mCommand, tmpParameters);
	this->setParameters(iterator, tmpParameters);
	this->mSize = this->mTotalMessage.length();
}

Message::~Message()
{}

void Message::skipSpace(std::string::const_iterator &iterator, const std::string &message)
{
	while (*iterator == ' ' && iterator != message.end())
		++iterator;
}

void Message::setTotalMessage(const std::string &prefix, const std::string &command, const std::string &parameters)
{
	mTotalMessage = prefix;
	if (prefix != "")
		mTotalMessage += " ";
	mTotalMessage += command;
	if (parameters != "")
		mTotalMessage += " ";
	mTotalMessage += parameters;
}

void Message::setString(std::string &target, std::string::const_iterator &iterator, const std::string &message)
{
	target = "";
	while (*iterator != ' ' && *iterator != '\r' && *iterator != '\n' && iterator != message.end())
	{
		target += *iterator;
		++iterator;
	}
	this->skipSpace(iterator, message);
}

void Message::setParameters(std::string::const_iterator &iterator, const std::string &message)
{
	std::string parameter;

	while (*iterator != '\r' && *iterator != '\n')
	{
		if (*iterator == ':')
		{
			parameter = "";
			while (*iterator != '\r' && *iterator != '\n' && iterator != message.end())
			{
				parameter += *iterator;
				++iterator;
			}
			this->setVector(mParams, parameter);
		}
		else
		{
			this->setString(parameter, iterator, message);
			this->setVector(mParams, parameter);
		}
	}
}

void Message::setVector(std::vector<std::string> &vector, std::string &parameter)
{
	vector.push_back(parameter);
	parameter = "";
}

const std::string &Message::getPrefix(void) const
{
	return (mPrefix);
}

const std::string &Message::getCommand(void) const
{
	return (mCommand);
}

const std::string &Message::getParameter(const int &index) const
{
	return (mParams[index]);
}

const std::vector<std::string> &Message::getParameters(void) const
{
	return (mParams);
}

const std::string &Message::getTotalMessage(void) const
{
	return (mTotalMessage);
}
