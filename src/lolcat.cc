//
// Created by user on 07.01.23.
//

#ifndef MCPELAUNCHER_LOLCAT_CC_H
#define MCPELAUNCHER_LOLCAT_CC_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <time.h>

#if defined _WIN32 || defined _WIN64
#include <Windows.h>

	const HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	struct WinConsoleColor
	{
		int col;

		WinConsoleColor(const int& Col)
		{
			col = Col;
		}

		WinConsoleColor(const int& foreground, const int& background)
		{
			col = foreground + background*16;
		}
	};

	std::ostream& operator<<(std::ostream& os, const WinConsoleColor& cc)
	{
		if(&os == &std::cout)
		{
			FlushConsoleInputBuffer(hConsole);
			SetConsoleTextAttribute(hConsole, cc.col);
		}

		return os;
	}

	int noColors = 9;
	WinConsoleColor c_white(15);
	std::vector<WinConsoleColor> colors = {WinConsoleColor(4),
	                                       WinConsoleColor(12),
	                                       WinConsoleColor(6),
	                                       WinConsoleColor(10),
	                                       WinConsoleColor(2),
	                                       WinConsoleColor(3),
	                                       WinConsoleColor(1),
	                                       WinConsoleColor(5),
	                                       WinConsoleColor(13)};

	void powershell_colours()
	{
		noColors = 7;
		c_white = WinConsoleColor(15, 5);
		colors = std::vector<WinConsoleColor>{WinConsoleColor(12, 5),
		                                      WinConsoleColor(14, 5),
		                                      WinConsoleColor(10, 5),
		                                      WinConsoleColor(2, 5),
		                                      WinConsoleColor(3, 5),
		                                      WinConsoleColor(9, 5),
		                                      WinConsoleColor(13, 5)};
	}
#else
const int noColors = 30;
const std::string c_white  =  "\033[0m";
const std::string colors[] = {"\033[38;5;39m",
                              "\033[38;5;38m",
                              "\033[38;5;44m",
                              "\033[38;5;43m",
                              "\033[38;5;49m",
                              "\033[38;5;48m",
                              "\033[38;5;84m",
                              "\033[38;5;83m",
                              "\033[38;5;119m",
                              "\033[38;5;118m",
                              "\033[38;5;154m",
                              "\033[38;5;148m",
                              "\033[38;5;184m",
                              "\033[38;5;178m",
                              "\033[38;5;214m",
                              "\033[38;5;208m",
                              "\033[38;5;209m",
                              "\033[38;5;203m",
                              "\033[38;5;204m",
                              "\033[38;5;198m",
                              "\033[38;5;199m",
                              "\033[38;5;163m",
                              "\033[38;5;164m",
                              "\033[38;5;128m",
                              "\033[38;5;129m",
                              "\033[38;5;93m",
                              "\033[38;5;99m",
                              "\033[38;5;63m",
                              "\033[38;5;69m",
                              "\033[38;5;33m"};
#endif

bool file_exists(const std::string& path)
{
    struct stat info;

    if(stat(path.c_str(), &info) != 0) //path does not exist
        return 0;
    else if(info.st_mode & S_IFDIR)    //directory
        return 0;
    else                               //file
        return 1;
}

bool format = 0;
int tabWidth = 2;

int mod_val;
int mod(const int& x, const int& m)
{
    if(x >= 0)
        return x%m;
    else
    {
        mod_val = (-x)%m;
        if(mod_val)
            return m-mod_val;
        else
            return 0;
    }
}

double gradient = 999;
size_t width, cWidth;

bool addLineNo = 0, zigzag = 0;
int posGrad = 1;

int lolcat(std::istream& is)
{
    std::string inLine;
    int color,
            lineNo = 0,
            r = rand()%noColors;

    if(gradient < 0)
        gradient = -gradient;

    while(!is.eof())
    {
        if(!getline(is, inLine))
            continue;

        if(addLineNo)
            inLine = std::to_string(lineNo) + ": " + inLine;

        if(zigzag)
        {
            if(int(std::floor(lineNo/noColors))%2)
                color = r = (r+1)%noColors;
            else
                color = r = mod(r-1, noColors);
        }
        else
        {
            if(posGrad)
            {
                cWidth = (1-((lineNo+r)*gradient - std::floor((lineNo+r)*gradient))/1.0)*width;
                color = int((lineNo+r)*gradient)%noColors;
            }
            else
            {
                cWidth = (((lineNo+r)*gradient - std::floor((lineNo+r)*gradient))/1.0)*width;
                color = mod(-int((lineNo+r)*gradient), noColors);
                //color = mod(noColors-int((lineNo+r)*gradient)%noColors, noColors); //alternative to above
            }
        }


        size_t i=0;
        std::cout << colors[color];

        while(i < inLine.size())
        {
            for(size_t I=0; I<width && i<inLine.size(); ++I)
            {
                if(format)
                {
                    while(inLine[i] == '\t')
                    {
                        std::cout << std::string(tabWidth, ' ');
                        ++i;
                    }

                    //https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
                    while(format && i < inLine.size() && ((inLine[i] == '\\' && (!i || inLine[i-1] != '\\')) ||
                                                          inLine[i] == '\x0' ||
                                                          inLine[i] == '\xB0' ||         // degree
                                                          inLine.substr(i, 2) == "°" ||  // degree
                                                          inLine[i] == '\xF0' ||         // emojis
                                                          inLine[i] == '\xE2' ||         // emojis
                                                          inLine[i] == '\xC2' ||         // emojis
                                                          //inLine[i] == "\e" ||
                                                          inLine[i] == '\033' ||         // octag
                                                          inLine.substr(i, 2) == "^[" || // ctrl key
                                                          inLine[i] == '\x1b' ||         // hexadecimal
                                                          inLine[i] == '\u001b'))        // unicode
                    {
                        int start = i++;
                        while(i < inLine.size() && /*inLine[i] != 'm' && */
                              inLine[i] != -80 &&
                              inLine[i] != -92 &&
                              inLine[i] != ' ' &&
                              inLine[i] != '\n' &&
                              inLine[i] != '\t')
                            ++i;
                        std::cout << inLine.substr(start, i-start);

                        if(inLine[i] == ' ')
                            std::cout << colors[color];
                    }
                }

                if(i < inLine.size())
                    std::cout << inLine[i++];
            }

            if(width != cWidth)
                cWidth = width;
            color=(color+1)%noColors;
            std::cout << colors[color];
        }


        if(&is == &std::cin)
            std::cout << c_white;

        std::cout << std::endl;
        ++lineNo;
    }

    std::cout << c_white << std::flush;

    return 0;
}

static int lineNo = 0;
int lolcat(const std::string& inLine)
{
    int color,
            r = rand()%noColors;

    if(gradient < 0)
        gradient = -gradient;


    if(zigzag)
        {
            if(int(std::floor(lineNo/noColors))%2)
                color = r = (r+1)%noColors;
            else
                color = r = mod(r-1, noColors);
        }
    else
        {
            if(posGrad)
            {
                cWidth = (1-((lineNo+r)*gradient - std::floor((lineNo+r)*gradient))/1.0)*width;
                color = int((lineNo+r)*gradient)%noColors;
            }
            else
            {
                cWidth = (((lineNo+r)*gradient - std::floor((lineNo+r)*gradient))/1.0)*width;
                color = mod(-int((lineNo+r)*gradient), noColors);
                //color = mod(noColors-int((lineNo+r)*gradient)%noColors, noColors); //alternative to above
            }
        }


       // size_t i=0;
        std::cout << colors[color];
    /*format = true;
        while(i < inLine.size())
        {
           // i++;
            std::cout << "while " << i << "\n";
            for(size_t I=0; I<width && i<inLine.size(); ++I)
            {
                if(format)
                {

                    //https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
                    while(format && i < inLine.size() && ((inLine[i] == '\\' && (!i || inLine[i-1] != '\\')) ||
                                                          inLine[i] == '\x0' ||
                                                          inLine[i] == '\xB0' ||         // degree
                                                          inLine.substr(i, 2) == "°" ||  // degree
                                                          inLine[i] == '\xF0' ||         // emojis
                                                          inLine[i] == '\xE2' ||         // emojis
                                                          inLine[i] == '\xC2' ||         // emojis
                                                          //inLine[i] == "\e" ||
                                                          inLine[i] == '\033' ||         // octag
                                                          inLine.substr(i, 2) == "^[" || // ctrl key
                                                          inLine[i] == '\x1b' ||         // hexadecimal
                                                          inLine[i] == '\u001b'))        // unicode
                    {
                        int start = i++;
                        while(i < inLine.size() &&
                              inLine[i] != -80 &&
                              inLine[i] != -92 &&
                              inLine[i] != ' ' &&
                              inLine[i] != '\n' &&
                              inLine[i] != '\t')
                            ++i;
                        std::cout << inLine.substr(start, i-start);

                        if(inLine[i] == ' ')
                            std::cout << colors[color];
                    }
                }

                if(i < inLine.size())
                    std::cout << inLine[i++];
            }

            if(width != cWidth)
                cWidth = width;
            color=(color+1)%noColors;
            std::cout << colors[color];
        }



        std::cout << std::endl;
        ++lineNo;*/
   std::cout << inLine << colors[color];


    std::cout << c_white << std::flush;

    return 0;
    }


int lolfilter(std::istream &is)
{
    if(width == 0)
    {
#if defined _WIN32 || defined _WIN64
        width = 7;
#else
        width = 4;
#endif
    }

    if(gradient != 999)
        return lolcat(is);
    else if(zigzag)
        return lolcat(is);
#if defined _WIN32 || defined _WIN64
#else
    else if(!(rand()%3))
    {
        zigzag = 1;
        return lolcat(is);
    }
#endif
    else
    {
        gradient = 0.6;
        posGrad = rand()%2;
    }

    return lolcat(is);
}


#endif //MCPELAUNCHER_LOLCAT_CC_H
