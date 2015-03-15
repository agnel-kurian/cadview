# Introduction #

This is the big picture, a TODO list and a collection of ideas.


# Details #

Immediate:
  * Persistence/Serialization
  * Use **`cad_entity` base class**
  * **Remove "cad" prefix** except where it is required (outermost namespace, folder etc.)
  * **Selection set:** Selection is per view. Not per document. So, selected objects are marked as selected by adding them to a selection set. Selections can cross layers. On paint, if an object is selected, draw it using dashed-pen. Only one selection set will be supported initially. We could have support for more than one selection set which can be used programmatically. As for UI, only one selection set makes sense. Need to decide how to handle object which is selected in one view and deleted from another. What happens if all objects in a selection set in one view are deleted via another view.
  * **Y-axis** should increase upwards
  * Relative co-ordinates
  * Output console
  * **Toolbar** for gladeui
  * Execute commands from Command Line
  * **Serialization:** JSON, Protocol Buffers, Mercurial/Git repo, SQLite, Database
  * Converter (with ODA dependency) to convert DWG to cadview format
  * **POLYGON** command
  * **OFFSET** command
  * **LINE** tool
  * **CIRCLE** tool
  * Polar co-ordinates
  * **Layers**
  * **Prompt strings** should be displayed when requiring input
  * ~~**Keyboard input** should be enabled for `get_point`~~
  * **get\_string** function
  * **SELECT** command
  * **snap** feature
  * Blocks
  * Text
  * **Viewports:** Should allow a view to be embedded inside another. For example, a zoomed-in view of a part of a drawing as an inset. There is another name for this...