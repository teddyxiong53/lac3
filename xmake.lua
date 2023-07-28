set_project("lac")
set_xmakever("2.6.3")

set_version("0.0.1", {build = "%Y%m%d%H%M"})
add_rules("mode.debug", "mode.release")


add_defines("LINUX", "HAS_PTHREAD", "HAS_STD_MALLOC", "HAVE_CLOCK_GETTIME", "HAS_SEM_OPEN", "HAVE_SEM_TIMEDWAIT",
"HAS_GET_TIME_US64", "WITH_DATA_READER_WRITER", "HAS_STDIO"
)
add_includedirs("./src/common_header")

add_includedirs(
"./src/memcheck", 
"./src/ringbuffer",
"./src/elk", 
"./src/event_handler",
"./src/jsonrpc", 
"./src/libev",
"./src/tinyparam", 
"./src/tinythpool", 
"./src/lua/lua5.3", 
"./src/cjson"
)

add_links("c","m","rt", "pthread", "dl")


target("lac")
    -- set kind
    set_kind("shared")
    -- add deps
    add_files("src/memcheck/*.c")
    add_files("src/ringbuffer/*.c")
    add_files("src/cjson/*.c")
    add_files("src/elk/*.c")
    add_files("src/jsonrpc/*.c")
    add_files("src/libev/ev.c")
    add_files("src/tinyparam/*.c")
    add_files("src/tinythpool/*.c")
    add_files("src/lua/lua5.3/*.c")
    add_files("src/event_handler/*.c")
includes(
"test"
)
