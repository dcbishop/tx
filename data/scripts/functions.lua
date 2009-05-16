function getTimeDiff()
	return (self.last_update - time) / 1000
end

function getObjectByTag(tag)
	return gm:getObjectByTag(tag)
end

function getAreaByTag(tag)
	return gm:getAreaByTag(tag)
end

function getCreatureByTag(tag)
	return gm:getCreatureByTag(tag)
end

function getPlayer()
	return gm:getCreatureByTag("Player")
end

-- TODO: These functions are no longer needed here

-- Gets the distance to the object from self
function getDistanceTo(object)
	diff_x = object.x - self.x
	diff_z = object.z - self.z
	return math.sqrt(math.pow(diff_x, 2) + math.pow(diff_z, 2))
end

function getDirectionTo(object) 
	diff_x = object.x - self.x
	diff_z = object.z - self.z
	return math.atan2(diff_z, diff_x)
end

function hello()
	print("Hello")
end
