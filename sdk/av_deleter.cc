//
// Created by cuangenglei-os@360os.com on 2020/3/4.
//
#include "include/av_deleter.h"
#include "include/ffmpeg.h"

namespace ffmpeg {


template<>
void AVDeleter<AVInputFormat>::operator()(AVInputFormat *objPtr) {
  if (objPtr) {
    /// Noop
  }
}

template<>
void AVDeleter<AVDictionary>::operator()(AVDictionary *objPtr) {
  if (objPtr) {
    av_dict_free(&objPtr);
  }
}

template<>
void AVDeleter<AVCodecContext>::operator()(AVCodecContext *objPtr) {
  if (objPtr) {
    avcodec_free_context(&objPtr);
  }
}

template<>
void AVDeleter<AVIOContext>::operator()(AVIOContext *objPtr) {
  if (objPtr) {
    av_free(objPtr->buffer);
    av_free(objPtr);
  }
}

template<>
void AVDeleter<AVFormatContext>::operator()(AVFormatContext *objPtr) {
  if (objPtr) {
    avformat_close_input(&objPtr);
  }
}

template<>
void AVDeleter<AVPacket>::operator()(AVPacket *objPtr) {
  if (objPtr) {
    av_packet_free(&objPtr);
  }
}

template<>
void AVDeleter<AVFrame>::operator()(AVFrame *objPtr) {
  if (objPtr) {
    av_frame_free(&objPtr);
  }
}

template<>
void AVDeleter<SwrContext>::operator()(SwrContext *objPtr) {
  if (objPtr) {
    swr_free(&objPtr);
  }
}

template<>
void AVDeleter<AVFilterGraph>::operator()(AVFilterGraph *objPtr) {
  if (objPtr) {
    avfilter_graph_free(&objPtr);
  }
}

template<>
void AVDeleter<AVFilterContext>::operator()(AVFilterContext *objPtr) {
  if (objPtr) {
    /// Noop
  }
}

}