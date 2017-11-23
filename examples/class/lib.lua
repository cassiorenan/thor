stdlib_dependencies = {}

function processDependencies(t)
    function check (field, val, dep)
	    if field.type:match(val) then
		    stdlib_dependencies[dep==nil and val or dep] = true 
	    end
	end
    for _,field in pairs(t) do
        check(field, 'string');
		check(field, 'vector');
		check(field, 'unique_ptr', 'memory');
		check(field, 'shared_ptr', 'memory');
	end
end