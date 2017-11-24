test_values = {1, 2, true, "foo", 5.5}

function escape(v)
    if type(v) == 'string' then
	    return "\"" .. v .. "\"";
	else
	    return v;
	end
end
