str1 = "hello world";
--print(#str1);
--print(str1 .. "fujinghui")
a = {};
a[1] = "fasdf";
a[str1] = str1;
for k,v in pairs(a) do
	print(k .. ":" .. v);
end
