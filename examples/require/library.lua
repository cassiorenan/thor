function escape(v)
    if type(v) == 'string' then
	    return "\"" .. v .. "\"";
	else
	    return v;
	end
end
