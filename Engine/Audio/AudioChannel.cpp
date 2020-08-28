#include "pch.h"
#include "AudioChannel.h"

bool nc::AudioChannel::isPlaying()
{
    bool isPlaying = false;
    if (m_channel != nullptr)
    {
        m_channel->isPlaying(&isPlaying);
    }
    return isPlaying;
}

void nc::AudioChannel::Stop()
{
    if (isPlaying())
    {
        m_channel->stop();
    }
}
