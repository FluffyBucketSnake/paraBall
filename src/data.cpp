#include <data.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <exception>

Data::Data Data::_data;

std::string *Data::_path = nullptr;
std::fstream *Data::_stream = nullptr;

void Data::Reset()
{
    //Graphics related stuff.
    _data.Fullscreen = 0;
    _data.WindowWidth = 320;
    _data.WindowHeight = 240;
    _data.MaxFPS = 60;
    //Sound related stuff.
    _data.MasterVolume = SDL_MIX_MAXVOLUME;
    //Player statistic related stuff.
    _data.Highscore = 0;
}

void Data::_assert()
{
    if (!IsOpen())
        throw new std::ios_base::failure("No data file is open.");
}

bool Data::IsOpen()
{
    return (_stream != nullptr);
}

void Data::Open(const std::string &path)
{
    //Check if a data file is already open.
    if (IsOpen())
        throw new std::ios_base::failure("A data file is already open.");
    //If file doesn't exists, create a new one.
    _stream = new std::fstream(path, std::fstream::out);
    _stream->close();
    //Finally open the file.
    _stream->open(path, std::fstream::out | std::fstream::binary | std::fstream::in);
    _path = new std::string(path);
}

void Data::Load()
{
    //Assert file being open.
    _assert();
    //Move stream to the beggining.
    _stream->seekg(std::ios_base::beg);
    //Check file header.
    char header[3];
    _stream->read(header, sizeof(char) * 3);
    if (header[0] == 'p' && header[1] == 'B' && header[2] == 'd')
    {
        //If header is valid, read each value.
        //Graphics.
        _stream->read((char *)&_data.Fullscreen, sizeof(Uint32));
        _stream->read((char *)&_data.WindowWidth, sizeof(int));
        _stream->read((char *)&_data.WindowHeight, sizeof(int));
        _stream->read((char *)&_data.MaxFPS, sizeof(int));
        //Sound.
        _stream->read((char *)&_data.MasterVolume, sizeof(int));
        //Statistics.
        _stream->read((char *)&_data.Highscore, sizeof(int));
    }
    else
    {
        //Otherwise, reset and save default data.
        Reset();
        Save();
    }
}

void Data::Save()
{
    //Assert file being open.
    _assert();
    //Move stream to the beggining.
    _stream->seekp(std::ios_base::beg);
    //Write header.
    char header[3] = {'p', 'B', 'd'};
    _stream->write(header, 3 * sizeof(char));
    //Write values.
    //Graphics.
    _stream->write((char *)&_data.Fullscreen, sizeof(Uint32));
    _stream->write((char *)&_data.WindowWidth, sizeof(int));
    _stream->write((char *)&_data.WindowHeight, sizeof(int));
    _stream->write((char *)&_data.MaxFPS, sizeof(int));
    //Sound.
    _stream->write((char *)&_data.MasterVolume, sizeof(int));
    //Statistics.
    _stream->write((char *)&_data.Highscore, sizeof(int));
    _stream->flush();
}

void Data::Close()
{
    _stream->close();
    delete _stream;
    delete _path;
    _stream = nullptr;
    _path = nullptr;
}

const std::string &Data::GetCurrentPath()
{
    return *_path;
}

void Data::ToggleFullscreen(Uint32 value)
{
    _data.Fullscreen = value;
}

Uint32 Data::GetFullscreen()
{
    return _data.Fullscreen;
}

void Data::SetResolution(int width, int height)
{
    _data.WindowWidth = width;
    _data.WindowHeight = height;
}

void Data::GetResolution(int &width, int &height)
{
    width = _data.WindowWidth;
    height = _data.WindowHeight;
}

void Data::SetMaxFPS(int value)
{
    _data.MaxFPS = value;
}

int Data::GetMaxFPS()
{
    return _data.MaxFPS;
}

void Data::SetMasterVolume(int value)
{
    if (value > SDL_MIX_MAXVOLUME)
        _data.MasterVolume = SDL_MIX_MAXVOLUME;
    else if (value < 0)
        _data.MasterVolume = 0;
    else
        _data.MasterVolume = value;
}

int Data::GetMasterVolume()
{
    return _data.MasterVolume;
}

void Data::SetHighscore(int value)
{
    _data.Highscore = value;
}

int Data::GetHighscore()
{
    return _data.Highscore;
}