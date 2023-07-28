add_deps("lac"
)

function get_files(pattern)
  local res = {}
  for _, fi in ipairs(os.files(pattern)) do
    Item = {path = "", dir = "", filename = "", basename = "", ext = ""}
    local item = Item
    item.path = fi
    item.dir, item.filename, item.ext = fi:match("^(.-)([^\\/]-%.([^\\/%.]-))%.?$")
    item.basename = item.filename:gsub("%."..item.ext.."$","")
    table.insert(res, item)
  end
  return ipairs(res)
end

for _, fi in get_files("*.c") do
target(fi.basename)
    set_kind("binary")
    add_files(fi.path)
end
