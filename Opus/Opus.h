#pragma once

#ifdef OPUS_EXPORTS
#define OPUS_API __declspec(dllexport)
#else
#define OPUS_API __declspec(dllimport)
#endif
