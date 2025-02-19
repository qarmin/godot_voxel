#ifndef VOXEL_GRAPH_EDITOR_IO_DIALOG_H
#define VOXEL_GRAPH_EDITOR_IO_DIALOG_H

#include "../../generators/graph/voxel_graph_function.h"
#include "../../util/godot/confirmation_dialog.h"
#include "../../util/godot/editor_undo_redo_manager.h"

ZN_GODOT_FORWARD_DECLARE(class ItemList)
ZN_GODOT_FORWARD_DECLARE(class LineEdit)
ZN_GODOT_FORWARD_DECLARE(class OptionButton)
ZN_GODOT_FORWARD_DECLARE(class SpinBox)
ZN_GODOT_FORWARD_DECLARE(class Button)

namespace zylann::voxel {

// Dialog to edit exposed inputs and outputs of a `VoxelGraphFunction`
class VoxelGraphEditorIODialog : public ConfirmationDialog {
	GDCLASS(VoxelGraphEditorIODialog, ConfirmationDialog)
public:
	VoxelGraphEditorIODialog();

	void set_graph(Ref<VoxelGraphFunction> graph);
	void set_undo_redo(Ref<EditorUndoRedoManager> undo_redo);

private:
	void set_enabled(bool enabled);

	void _on_auto_generate_button_pressed();
	void _on_ok_pressed();

	void reshow(Ref<VoxelGraphFunction> graph);

	void process();

	void _notification(int p_what);

	struct PortsUI {
		ItemList *item_list = nullptr;
		LineEdit *name = nullptr;
		OptionButton *usage = nullptr;
		SpinBox *default_value = nullptr;
		Button *add = nullptr;
		Button *remove = nullptr;
		Button *move_up = nullptr;
		Button *move_down = nullptr;
		int selected_item = -1;
	};

	static Control *create_ui(PortsUI &ui, String title, bool has_default_values);
	static void set_enabled(PortsUI &ui, bool enabled);
	static void clear(PortsUI &ui);
	void copy_ui_to_data(const PortsUI &ui, std::vector<VoxelGraphFunction::Port> &ports);
	void copy_data_to_ui(PortsUI &ui, const std::vector<VoxelGraphFunction::Port> &ports);
	void process_ui(PortsUI &ui, std::vector<VoxelGraphFunction::Port> &ports);

	static void _bind_methods();

	Ref<VoxelGraphFunction> _graph;
	std::vector<VoxelGraphFunction::Port> _inputs;
	std::vector<VoxelGraphFunction::Port> _outputs;

	PortsUI _inputs_ui;
	PortsUI _outputs_ui;
	Button *_auto_generate_button = nullptr;
	Ref<EditorUndoRedoManager> _undo_redo;
};

} // namespace zylann::voxel

#endif // VOXEL_GRAPH_EDITOR_IO_DIALOG_H
