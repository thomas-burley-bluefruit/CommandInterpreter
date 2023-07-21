Command mCurrentCommand;
size_t mCommandIndex;

Terminal::OnReceive(uint8_t character)
{
    mCurrentCommand.Buffer[mCommandIndex++] = character;
    if (character == \n)
    {
        mCommandInterpreter.Interpret(mCurrentCommand);
    }

    if (mCurrentCommant.IsValid() == false)
        return;

    switch(mCurrentCommand.GetCommandName())
    {
        case CommandName::Foo:
            mFoo.onCommand(mCurrentCommand);
    }
}