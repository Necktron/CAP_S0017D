#!/bin/bash
#!/bin/sh

file="ShellTest/CopyrightInfo.txt"

numOfFile=0

echo "Necktrons ShellScript v1.0 - BOOTED"
echo "Knowledge is power...!"
echo ""

while :
do
    echo "What do you want to do?"
    echo "1. Copyright header to file"
    echo "2. Rename .cpp to .cc and then back again"
    echo "3. Replace float with double and then back again"
    read Command
    echo ""

    if (($Command == "1"));
    then
        echo "Copyright stamp in file"
	echo ""
	echo "What file would you like to edit?"
	read FileToEdit
	echo ""

	if [[ -f "ShellTest/$FileToEdit" ]]
	then
	    echo "The file exsists"
	    cat $file ShellTest/$FileToEdit > tmp && mv tmp ShellTest/$FileToEdit

	else
	    echo "The file does not exsist"
	fi

    elif (($Command == "2"));
    then
    	echo "Renaming from .cpp to .cc and then back again"
	echo ""

	if (find ShellTest -name '*.cpp')
	then

	    echo ".cpp files has been located, changing all .cpp files!"

	    for file in $(find ShellTest -name '*.cpp')
	    do
	    	mv $file $(echo "$file" | sed -r 's|.cpp|.cc|g')
	    done

	    echo "The file has been changed, please do confirm that the change has been made"
	    echo "Results will be reverted to normal in 30 sec, hurry!"

	    sleep 30

	    for file in $(find ShellTest -name '*.cc')
	    do
	        mv $file $(echo "$file" | sed -r 's|.cc|.cpp|g')
	    done

	elif (find ShellTest '*.h')
	then

	    echo "No .cpp files has been located, changing all .h files!"

	    for file in $(find ShellTest -name '*.h')
	    do
	    	mv $file $(echo "$file" | sed -r 's|.h|.hpp|g')
	    done

	    echo "The file has been changed, please do confirm that the change has been made"
	    echo "Results will be reverted to normal in 30 sec, hurry!"

	    sleep 30

	    for file in $(find ShellTest -name '*.hpp')
	    do
	        mv $file $(echo "$file" | sed -r 's|.hpp|.h|g')
	    done

	    echo "No .cpp files has been located, changing all .h files!"

	else
	    echo "No files found worth of modifying"
	    echo "Please control that the map ShellTest contains any .cpp or .h files!"
	fi

    elif (($Command == "3"));
    then
	echo "Replacing float with double and then back again"
	echo ""
	echo "What file would you like to edit?"
	read FileToEdit
	echo ""
	if [[ -f "ShellTest/$FileToEdit" ]]
	then
	    echo "The file exsists"

	    sed -i -e 's/float /double /g' ShellTest/$FileToEdit

	    echo "The file has been changed, please do confirm that the change has been made"
	    echo "Results will be reverted to normal in 30 sec, hurry!"

	    sleep 30

	    sed -i -e 's/double /float /g' ShellTest/$FileToEdit

	else
	    echo "The file does not exsist"
	fi

    else
	echo "WTF are you doing?? Behave! \(*__*)"
	echo ""
    fi
done
