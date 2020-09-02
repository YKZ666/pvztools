/*
 * @Author: lmintlcx 
 * @Date: 2018-06-29 19:17:18 
 * @Description: Pack and unpack ".pak" file.
 */

#pragma once

#include <QObject>

#include <string>
#include <vector>

#include <Windows.h>

namespace Pt
{

#define UNPACK_SUCCESS 0           // 解包成功
#define UNPACK_SRC_NOT_EXIST 1     // 打开源文件失败
#define UNPACK_SRC_SIZE_ERROR 2    // 获取源文件大小失败
#define UNPACK_SRC_LOAD_ERROR 3    // 读取源文件内容失败
#define UNPACK_SRC_HEADER_ERROR 4  // 文件头格式不正确
#define UNPACK_SRC_DATA_ERROR 5    // 文件大小与索引区数据不符
#define UNPACK_PATH_CREATE_ERROR 6 // 解包路径创建失败
#define UNPACK_FILE_CREATE_ERROR 7 // 解包文件创建失败
#define UNPACK_FILE_WRITE_ERROR 8  // 解包文件写入失败

#define PACK_SUCCESS 0           // 打包成功
#define PACK_SRC_NOT_EXIST 1     // 打开源文件夹失败
#define PACK_SRC_EMPTY_ERROR 2   // 源文件夹为空
#define PACK_PATH_CREATE_ERROR 3 // 打包路径创建失败
#define PACK_FILE_CREATE_ERROR 4 // 打包文件创建失败
#define PACK_FILE_WRITE_ERROR 5  // 打包文件写入失败
#define PACK_SRC_READ_ERROR 6    // 打包源文件读取失败

class PAK : public QObject
{
    Q_OBJECT

public:
    PAK();
    ~PAK();

private:
    std::string utf8_encode(const std::wstring &);
    std::wstring utf8_decode(const std::string &);

    // 递归地创建文件夹
    bool create_path(const std::wstring &);

    // 递归地查找所有文件
    void find_files(const std::wstring,
                    std::vector<std::wstring> &, //
                    std::vector<int> &,          //
                    std::vector<FILETIME> &);

public:
    // 解包, 参数分别为源文件名和解包文件夹
    int Unpack(std::wstring, std::wstring);
    int Unpack(std::string, std::string);

    // 打包, 参数分别为源文件夹和打包文件名
    int Pack(std::wstring, std::wstring);
    int Pack(std::string, std::string);

    void UnpackPAK(QString, QString);
    void PackPAK(QString);

signals:
    void ShowMessageBox(QString);
    void ShowMessageStatusBar(QString);
    void UnpackFinished();
    void PackFinished();
};

} // namespace Pt
