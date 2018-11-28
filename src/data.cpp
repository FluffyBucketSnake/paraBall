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
    _data.FPSCap = 60;
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
    _stream = new std::fstream(path, std::fstream::in | std::fstream::out | std::fstream::binary);
    (*_path) = path;
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
        _stream->read((char *)&_data.Fullscreen, sizeof(uint8_t));
        _stream->read((char *)&_data.WindowWidth, sizeof(uint32_t));
        _stream->read((char *)&_data.WindowHeight, sizeof(uint32_t));
        _stream->read((char *)&_data.FPSCap, sizeof(uint8_t));
        //Sound.
        _stream->read((char *)&_data.MasterVolume, sizeof(int8_t));
        //Statistics.
        _stream->read((char *)&_data.Highscore, sizeof(uint32_t));
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
    _stream->write((char *)&_data.Fullscreen, sizeof(uint8_t));
    _stream->write((char *)&_data.WindowWidth, sizeof(uint32_t));
    _stream->write((char *)&_data.WindowHeight, sizeof(uint32_t));
    _stream->write((char *)&_data.FPSCap, sizeof(uint8_t));
    //Sound.
    _stream->write((char *)&_data.MasterVolume, sizeof(int8_t));
    //Statistics.
    _stream->write((char *)&_data.Highscore, sizeof(uint32_t));
}

void Data::Close()
{
    _stream->close();
    delete _stream;
    _stream = nullptr;
    _path = nullptr;
}