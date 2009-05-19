--print("hello")
--area = getAreaByTag('TestArea');
--print(self:getGridX() .. "x" .. self:getGridY())
--a = class_info(Object)
--object = Object("Test")
--info 
--print(type(class_info(Object))

--vmodel2 = VModel("Cube.dae")
object = getCreatureByTag("Player")
info = class_info(object)
print(info.name)
