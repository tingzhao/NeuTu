#include "taskio.h"

#include "logging/zqslog.h"
#include "zdvidutil.h"
#include "neutubeconfig.h"
#include "znetbufferreader.h"

namespace neutuse {

TaskIO::TaskIO()
{
}

TaskIO::~TaskIO()
{

}

void TaskIO::reset()
{
  m_address.clear();
  m_statusCode = 0;
  m_connected = false;
  m_response.clear();
  m_connection.reset();
}

void TaskIO::setStatusCode(int code)
{
  m_statusCode = code;
}

int TaskIO::getStatusCode() const
{
  return m_statusCode;
}

std::string TaskIO::getResponse() const
{
  return m_response;
}

void TaskIO::open(const std::string &server)
{
  try {
    m_connection = std::unique_ptr<libdvid::DVIDConnection>(
          new libdvid::DVIDConnection(server, GET_FLYEM_CONFIG.getUserName(),
                                      NeutubeConfig::GetSoftwareName()));
    m_address = server;
    testConnection();
  } catch (std::exception &e){
    m_connection.reset();
    LWARN() << "Failed to connect to" << server;
  }
}

bool TaskIO::ready() const
{
  return m_connected;
//  return (m_connection.get() != nullptr);
}

void TaskIO::testConnection()
{
  if (!m_address.empty() && m_connection) {
    ZNetBufferReader reader;
    m_connected = reader.hasHead(m_address.c_str());
  }
}

void TaskIO::post(const std::string &path, const ZJsonObject &obj)
{
  if (ready()) {
    libdvid::BinaryDataPtr response = dvid::MakePostRequest(
          *m_connection, path, obj, m_statusCode);
    m_response = response->get_data();
  }
}

}
