#include <windows.h>
#include "logger.h"

void logger::set_color(const int forg_col)
{
	const auto h_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(h_std_out, &csbi))
	{
		const WORD w_color = (csbi.wAttributes & 0xF0) + (forg_col & 0x0F);
		SetConsoleTextAttribute(h_std_out, w_color);
	}
}

void logger::set_text(const char* text, const int color)
{
	set_color(color);
	char buf[256];
	sprintf_s(buf, ("\n %s"), text);
	printf(static_cast<const char*>(buf));
	set_color(White);
}

void logger::set_error(const char* text)
{
	set_color(Red);
	char buf[256];
	sprintf_s(buf, ("\n %s"), text);
	printf(static_cast<const char*>(buf));
	set_color(White);
}

void logger::set_warning(const char* text)
{
	set_color(Yellow);
	char buf[256];
	sprintf_s(buf, ("\n %s"), text);
	printf(static_cast<const char*>(buf));
	set_color(White);
}

void logger::set_ok(const char* text)
{
	set_color(Green);
	char buf[256];
	sprintf_s(buf, ("\n %s \n"), text);
	printf(static_cast<const char*>(buf));
	set_color(White);
}