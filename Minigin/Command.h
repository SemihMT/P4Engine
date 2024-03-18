#pragma once

//Command interface
class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};
