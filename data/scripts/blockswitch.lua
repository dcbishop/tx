-- When a block is pushed onto the tile, activate
if not globals[addr] then
	area = self.area
	gx = self:getGridX()
	gy = self:getGridY()
	tile = area:getTile(gx, gy)
	globals[addr] = VfxColour(1.0, 1.0, 0.0, 1.0)
	tile:addVfx(globals[addr])
end
