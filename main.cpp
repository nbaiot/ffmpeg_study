#include <iostream>
#include <string>
#include <memory>

#include <glog/logging.h>
#include <sdk/include/ffmpeg.h>
#include <sdk/include/av_deleter.h>
#include <bits/shared_ptr.h>

using namespace ffmpeg;

static void FFMPEGLog(void *ptr, int level, const char *fmt, va_list vl) {
  char buf[512] = {0};
  vsprintf(buf, fmt, vl);
  switch (level) {
    case AV_LOG_FATAL:
      LOG(FATAL) << buf;
      break;
    case AV_LOG_ERROR:
      LOG(ERROR) << buf;
      break;
    case AV_LOG_WARNING:
      LOG(WARNING) << buf;
      break;
    case AV_LOG_INFO:
    case AV_LOG_VERBOSE:
    case AV_LOG_DEBUG:
    default:
      LOG(INFO) << buf;
  }
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = google::INFO;

  avdevice_register_all();
  av_log_set_level(AV_LOG_INFO);
  av_log_set_callback(FFMPEGLog);
  /// 1. find v4l2 format
  auto input = av_find_input_format("v4l2");

  if (!input) {
    LOG(ERROR) << "current system not support v4l2";
    return -1;
  }
  LOG(INFO) << "v4l2 name:" << input->long_name;



  auto inputContext = std::shared_ptr<AVFormatContext>(avformat_alloc_context(), AVFormatContextDeleter());

  auto rawInputContextPtr = inputContext.get();


  /// list video device support format
  /// raw format and compressed format

  AVDictionary *opts = nullptr;
  /*av_dict_set_int(&opts, "list_formats", 3, 0);


  /// 耗时: 内部调用 read_header:v4l2_read_header
  /// 内部会自动释放 AVDictionary
  auto ret = avformat_open_input(&rawInputContextPtr, "/dev/video0", input, &opts);

  if (ret != 0 && ret != AVERROR_EXIT) {
    LOG(ERROR) << "avformat_open_input error:" << av_err2str(ret);
    return -1;
  }*/

//  av_dict_set(&opts, "input_format", "rgba", 0);
  av_dict_set(&opts, "input_format", "mjpeg", 0);
  av_dict_set(&opts, "video_size", "1280*720", 0);
  av_dict_set(&opts, "framerate", "30", 0);
  auto ret = avformat_open_input(&rawInputContextPtr, "/dev/video0", input, &opts);

  if (ret != 0) {
    LOG(ERROR) << "avformat_open_input error:" << av_err2str(ret);
    return -1;
  }

  /// AVInputFormat 中的函数指针，都需要传递 AVFormatContext*,
  /// 所以必须 avformat_open_input 后才能使用
  if (input->get_device_list) {
    struct AVDeviceInfoList infoList{};
    input->get_device_list(rawInputContextPtr, &infoList);
    LOG(INFO) << ">>>>>>>>>>>>>>v4l2 device info list:";
    for (int i = 0; i < infoList.nb_devices; ++i) {
      LOG(INFO) << "device_name:" << infoList.devices[i]->device_name;
      LOG(INFO) << "device_description:" << infoList.devices[i]->device_description;
    }
  }


  LOG(INFO) << "nb_streams:" << inputContext->nb_streams;
  if (inputContext->nb_streams > 0) {
    auto codecpar = inputContext->streams[0]->codecpar;
    LOG(INFO) << "codec type:" << av_get_media_type_string(codecpar->codec_type);
    LOG(INFO) << "codec name:" << avcodec_get_name(codecpar->codec_id);
    LOG(INFO) << "codec name:" << av_get_pix_fmt_name((AVPixelFormat)codecpar->format);
    LOG(INFO) << "width:" << inputContext->streams[0]->codecpar->width;
    LOG(INFO) << "height:" << inputContext->streams[0]->codecpar->height;
    LOG(INFO) << "frame rate:" << inputContext->streams[0]->avg_frame_rate.num / inputContext->streams[0]->avg_frame_rate.den;
  }

  return 0;
}