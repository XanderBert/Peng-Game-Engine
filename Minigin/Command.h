#pragma once


//You want your event and action code stored here?
//You can inherit from this class
//Keep track of the commands (To Undo) 
//https://www.youtube.com/watch?v=mSZuEbAkJCo

enum class InputType
{
	Down,
	Up,
	Pressed
};


class Command
{
public:
	Command(InputType type);
	virtual ~Command() = default;

	Command(const Command& other) = delete;
	Command(Command&& other)noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other)noexcept = delete;

	virtual void Execute() = 0;
	//virtual void Undo() = 0;
	//virtual void Merge(Command* other) = 0;

	InputType GetInputtType() const { return  m_InputType; }

private:
	InputType m_InputType;
};

inline Command::Command(InputType type) : m_InputType(type)
{}

