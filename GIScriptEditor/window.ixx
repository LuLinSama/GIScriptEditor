module;
#include <Windows.h>
export module window;

import std;
import util;
import render;
import widgets;

export namespace Editor::Base
{
	class Window
	{
		HWND handle;
		Render::Renderer renderer;
		std::deque<std::unique_ptr<UI::Widget>> widgets;
		UI::Widget* hovered = nullptr;
		UI::Widget* pop_widget = nullptr;
		Utils::Delegate<LRESULT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)> message;
	protected:
		LRESULT ProcMsg(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	public:
		explicit Window(const std::string& title);
		int Run();
		Utils::Future<void> Dialog(const std::wstring& title, const std::wstring& msg, UINT type) const;
		Utils::Future<std::wstring> OpenFile(const std::vector<std::pair<std::wstring, std::wstring>>& filters) const;
		Utils::Future<std::wstring> SaveFile(const std::wstring& default_ext = L"", const std::vector<std::pair<std::wstring, std::wstring>>& filters = {}) const;
		void Flush() const;

		const Render::Renderer& Renderer() const { return renderer; }
		void SetPop(UI::Widget& widget) { pop_widget = &widget; widget.visible = true; }

		template<typename T> requires std::is_base_of_v<UI::Widget, T>
		T& AddWidget(std::unique_ptr<T> widget)
		{
			return (T&)*widgets.emplace_back(std::move(widget));
		}
	};
}
