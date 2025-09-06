### Item Resource (Resource)
* Holds baked data about the item such as name, weight, description, etc.
* Can be extended by Item Extensions to define logic that will happen when an item is used, dropped, picked up, etc.

### Item Extension (Resource)
* Used for extending the logic and behavior of an Item Resource.
* Is referenced directly by the individual Item Resource
* Holds overridable methods like on use, picked up, etc.
* Enables extending logic by composition, a kin to a component system.

### Item Object (RefCounted)
* Generated during runtime when an Item is added to an inventory.
* References the Item Resource.
* Holds runtime dynamic data such as the amount in inventory.
* Doesn't have any overridable logic and shouldn't be inherited.
* Only responsible for storing runtime dynamic data to represent Item instances within an inventory.

### Inventory Node (Node)
* Holds a certain amount of Item Objects
* Knows how many items it holds
* Uses Stats System to define and modify the inventory capacity