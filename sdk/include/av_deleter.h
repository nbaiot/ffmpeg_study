//
// Created by cuangenglei-os@360os.com on 2020/3/4.
//
#pragma once

#ifndef FIGHTER_VIDEO_KITS_AV_DELETER_H
#define FIGHTER_VIDEO_KITS_AV_DELETER_H


struct AVInputFormat;
struct AVDictionary;
struct AVCodecContext;
struct AVIOContext;
struct AVFormatContext;
struct AVPacket;
struct AVFrame;
struct SwrContext;
struct AVFilterGraph;
struct AVFilterContext;

namespace ffmpeg {

template <typename AVObj>
class AVDeleter {
public:
  void operator()(AVObj* objPtr);
};

using AVInputFormatDeleter = AVDeleter<AVInputFormat>;
using AVDictionaryDeleter = AVDeleter<AVDictionary>;
using AVContextDeleter = AVDeleter<AVCodecContext>;
using AVIOContextDeleter = AVDeleter<AVIOContext>;
using AVFormatContextDeleter = AVDeleter<AVFormatContext>;
using AVPacketDeleter = AVDeleter<AVPacket>;
using AVFrameDeleter = AVDeleter<AVFrame>;
using SwrContextDeleter = AVDeleter<SwrContext>;
using AVFilterGraphDeleter = AVDeleter<AVFilterGraph>;
using AVFilterContextDeleter = AVDeleter<AVFilterContext>;

}

#endif //FIGHTER_VIDEO_KITS_AV_DELETER_H
