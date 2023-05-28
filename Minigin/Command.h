#pragma once
#include "iostream"
class GameActor;


//You want your event and action code stored here?
//You can inherit from this class
//Keep track of the commands (To Undo) (This can fix tunneling to undo the move on collision?)

//https://www.youtube.com/watch?v=mSZuEbAkJCo

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	Command(const Command& other) = delete;
	Command(Command&& other)noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other)noexcept = delete;

	virtual void Execute() = 0;
	//virtual void Undo() = 0;
	//virtual void Merge(Command* other) = 0;
};

