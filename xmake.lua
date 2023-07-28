set_project("lac")
set_xmakever("2.6.3")

set_version("0.0.1", {build = "%Y%m%d%H%M"})
add_rules("mode.debug", "mode.release")


add_defines("LINUX", "HAS_PTHREAD", "HAS_STD_MALLOC", "HAVE_CLOCK_GETTIME", "HAS_SEM_OPEN", "HAVE_SEM_TIMEDWAIT",
"HAS_GET_TIME_US64", "WITH_DATA_READER_WRITER", "HAS_STDIO"
)
add_includedirs("./src/common_header")

add_includedirs("./src/memcheck", "./src/ringbuffer")

add_links("c","m","rt", "pthread", "dl")


target("lac")
    -- set kind
    set_kind("shared")
    -- add deps
    add_files("src/memcheck/*.c")
    add_files("src/ringbuffer/*.c")


includes(
"test"
)
