cmake_minimum_required(VERSION 2.8)
set(CMAKE_EXE_LINKER_FLAGS -flto)

#for linking
set(OS_WHOLELINK_PRE "-Wl,-whole-archive")
set(OS_WHOLELINK_POST "-Wl,-no-whole-archive")

#cmake arguments
add_definitions(
-DBOOST_NETWORK_ENABLE_HTTPS 
-DBOOST_NO_CXX11_VARIADIC_TEMPLATES
-DDEBIAN_BASED=1
-DNDEBUG
-DOSQUERY_BUILD_DISTRO=trusty
-DOSQUERY_BUILD_PLATFORM=ubuntu
-DOSQUERY_BUILD_SDK_VERSION=2.3.0 
-DOSQUERY_THRIFT=\"\" 
-DOSQUERY_THRIFT_LIB=thrift 
-DOSQUERY_THRIFT_POINTER=boost 
-DOSQUERY_THRIFT_SERVER_LIB=thrift/server 
-DSTRIP_FLAG_HELP=1 
-DUBUNTU 
-DUBUNTU_TRUSTY
)

#clang compile options
add_compile_options(
-Wstrict-aliasing
-Wno-missing-field-initializers
-Wno-unused-local-typedef
-Wno-deprecated-register
-Wno-unknown-warning-option
-Wnon-virtual-dtor
-Wchar-subscripts
-Wpointer-arith
-Woverloaded-virtual
-Wformat
-Wformat-security
-Werror=format-security
-Wabi-tag
-fpermissive
-fstack-protector-all
-pipe
-fdata-sections
-ffunction-sections
-Os
-fPIE
-fpie
-fPIC
-fpic
-flto
-march=x86-64
-mno-avx
-Wall
-Wextra
-Wshadow
-pedantic
-Wuseless-cast
-Wno-c99-extensions
-Wno-zero-length-array
-Wno-unused-parameter
-Wno-gnu-case-range
)

#compiler 
set(CMAKE_CXX_COMPILER "/usr/local/osquery/bin/clang++")
set(CXX_COMPILE_FLAGS "")
set(CXX_COMPILE_FLAGS "${CXX_COMPILE_FLAGS} -std=c++14 -stdlib=libc++")

add_compile_options(-std=c++14 -stdlib=libstdc++)


#include directories for compilation
include_directories(SYSTEM "/home/stack/osquery/osquery/third-party/sqlite3")
include_directories("/usr/local/osquery/include/openssl")
include_directories("/home/stack/osquery/osquery/include/")
include_directories("/usr/local/osquery/lib")
include_directories("/home/stack/osquery/osquery")
include_directories(SYSTEM "/usr/local/osquery/include")
include_directories(SYSTEM "/usr/local/osquery/legacy/include")
include_directories("/home/stack/osquery/osquery/third-party/sysroots/linux")
include_directories("/home/stack/osquery/osquery/build/trusty/generated/gen-cpp")
include_directories("home/stack/osquery/osquery/build/trusty/osquery/")
include_directories("/usr/local/osquery/lib/")

#directories for linking
link_directories("/home/stack/osquery/osquery/build/trusty/osquery/")
link_directories("/usr/local/osquery/lib/")
link_directories("/usr/local/osquery/legacy/lib/")

#set target variable
set(target "libtest")

#create static library
add_library(${target} STATIC test.cpp)



#create executable
#add_executable(${target} demo.cpp)

#link libraries
target_link_libraries(${target} "${OS_WHOLELINK_PRE}")
find_library(OSQUERY libosquery.a)
target_link_libraries(${target} ${OSQUERY})
target_link_libraries(${target} "${OS_WHOLELINK_POST}")
target_link_libraries(${target} "${OS_WHOLELINK_PRE}")
target_link_libraries(${target} "/home/stack/osquery/osquery/build/trusty/osquery/libosquery_additional.a")
target_link_libraries(${target} "${OS_WHOLELINK_POST}")
target_link_libraries(${target} "/usr/local/osquery/legacy/lib/libz.so")
target_link_libraries(${target} "-Wl,-Bstatic")
target_link_libraries(${target}  boost_system-mt  boost_filesystem-mt thrift gflags  glog)
target_link_libraries(${target} "-Wl,-Bdynamic")
target_link_libraries(${target} "/usr/local/osquery/legacy/lib/libdl.so")
target_link_libraries(${target} "/usr/local/osquery/legacy/lib/librt.so")
target_link_libraries(${target} c)
target_link_libraries(${target} "-rdynamic -Wl,-zrelro -Wl,-znow -pie")
target_link_libraries(${target} gcc_s)
target_link_libraries(${target} "-Wl,--build-id -static-libstdc++ -Wl,-Bstatic")
target_link_libraries(${target} cppnetlib-uri cppnetlib-client-connections boost_regex-mt rocksdb_lite snappy ssl)
target_link_libraries(${target} yara)
target_link_libraries(${target} crypto)
target_link_libraries(${target} "-Wl,-Bdynamic")
target_link_libraries(${target}  pthread)
target_link_libraries(${target} "-Wl,-Bstatic")
target_link_libraries(${target}  linenoise udev audit aws-cpp-sdk-kinesis aws-cpp-sdk-firehose aws-cpp-sdk-sts aws-cpp-sdk-core)
target_link_libraries(${target} "-Wl,-Bdynamic")
target_link_libraries(${target} "/usr/local/osquery/legacy/lib/libresolv.so")
target_link_libraries(${target} "-Wl,-Bstatic")
target_link_libraries(${target} cryptsetup devmapper gcrypt gpg-error blkid ip4tc magic tsk apt-pkg dpkg lz4 lzma bz2 rpm rpmio beecrypt popt db augeas fa xml2 uuid)
target_link_libraries(${target} "-Wl,-Bdynamic")

#for removing default rpath of executable
set_target_properties(${target} PROPERTIES SKIP_BUILD_RPATH TRUE)

