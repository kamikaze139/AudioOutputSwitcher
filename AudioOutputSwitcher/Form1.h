#pragma once

#include <vcclr.h>
//#include <stdio.h>
#include <wchar.h>
#include <tchar.h>
#include <string>

#undef DEFINE_PROPERTYKEY
#define DEFINE_PROPERTYKEY(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8, pid) EXTERN_C const PROPERTYKEY DECLSPEC_SELECTANY name = { { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }, pid }

DEFINE_PROPERTYKEY(PKEY_Device_DeviceDesc, 0xa45c254e, 0xdf1c, 0x4efd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0, 2);
DEFINE_PROPERTYKEY(PKEY_Device_FriendlyName, 0xa45c254e, 0xdf1c, 0x4efd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0, 14);
DEFINE_PROPERTYKEY(PKEY_DeviceInterface_FriendlyName,  0x026e516e, 0xb814, 0x414b, 0x83, 0xcd, 0x85, 0x6d, 0x6f, 0xef, 0x48, 0x22, 2); // DEVPROP_TYPE_STRING


// Format default string for outputing a device entry. The following parameters will be used in the following order:
// Index, Device Friendly Name
#define DEVICE_OUTPUT_FORMAT "Audio Device %d: %ws"

struct TGlobalState
{
	HRESULT hr;
	int option;
	IMMDeviceEnumerator *pEnum;
	IMMDeviceCollection *pDevices;
	LPWSTR strDefaultDeviceID;
	IMMDevice *pCurrentDevice;
	LPCWSTR pDeviceFormatStr;
	int deviceStateFilter;
};

HRESULT printDeviceInfo(IMMDevice* pDevice, int index, LPCWSTR outFormat, LPWSTR strDefaultDeviceID);
std::wstring getDeviceProperty(IPropertyStore* pStore, const PROPERTYKEY key);
HRESULT SetDefaultAudioPlaybackDevice(LPCWSTR devID);
void invalidParameterHandler(const wchar_t* expression, const wchar_t* function, const wchar_t* file,
unsigned int line, uintptr_t pReserved);

namespace AudioOutputSwitcher {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::NotifyIcon^  notifyIcon1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip2;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;

	protected: 
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->notifyIcon1 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->contextMenuStrip2 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip2->SuspendLayout();
			this->SuspendLayout();
			// 
			// notifyIcon1
			// 
			this->notifyIcon1->BalloonTipText = L"AudioSwitcher";
			this->notifyIcon1->BalloonTipTitle = L"";
			this->notifyIcon1->ContextMenuStrip = this->contextMenuStrip2;
			this->notifyIcon1->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"notifyIcon1.Icon")));
			this->notifyIcon1->Text = L"AudioOutputSwitcher";
			this->notifyIcon1->Visible = true;
			this->notifyIcon1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::notifyIcon1_MouseClick);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// contextMenuStrip2
			// 
			this->contextMenuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->exitToolStripMenuItem});
			this->contextMenuStrip2->Name = L"contextMenuStrip2";
			this->contextMenuStrip2->Size = System::Drawing::Size(93, 26);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(92, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->ShowInTaskbar = false;
			this->Text = L"Audioswitcher";
			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->contextMenuStrip2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
		{
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler (this, &Form1::Form1_Closed);
		}

		private: System::Void Form1_Closed(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
        {
            notifyIcon1->Visible = false;
        }

		public:	System::Void AddDevice(System::String^ name, System::String^ id, bool isDefault)
		{
			auto item = (gcnew System::Windows::Forms::ToolStripMenuItem());
			item->Name = id;
			item->Size = System::Drawing::Size(93, 22);
			item->Text = name;
			item->Click += gcnew System::EventHandler(this, &Form1::testToolStripMenuItem_Click);
			if (isDefault)
			{
				item->Font = gcnew System::Drawing::Font( item->Font,FontStyle::Bold );
			}
			else
			{
				item->Font = gcnew System::Drawing::Font( item->Font,FontStyle::Regular );
			}

			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {item});
		}


		private: System::Void testToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^  e) 
		{
			System::Windows::Forms::ToolStripItem^ item = (System::Windows::Forms::ToolStripItem^)sender;

			IPolicyConfigVista *pPolicyConfig;
			ERole reserved = eConsole;

			HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigVistaClient),
			NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID *)&pPolicyConfig);
			if (SUCCEEDED(hr))
			{

				pin_ptr<const wchar_t> devID = PtrToStringChars(item->Name);

				hr = pPolicyConfig->SetDefaultEndpoint(devID, reserved);
				pPolicyConfig->Release();
			}
		}
		private: System::Void notifyIcon1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)  
		{
			if (e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				UpdateDeviceList();

				this->notifyIcon1->ContextMenuStrip = this->contextMenuStrip1;
				
				mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);

			}
			else if (e->Button == System::Windows::Forms::MouseButtons::Right)
			{
				this->notifyIcon1->ContextMenuStrip = this->contextMenuStrip2;
			}
		}

		private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			exit(1);
		}

		private: System::Void UpdateDeviceList()
		{
			this->contextMenuStrip1->Items->Clear();

			TGlobalState state;

			// Process command line arguments
			state.option = 0; // 0 indicates list devices.
			state.strDefaultDeviceID = '\0';
			state.pDeviceFormatStr = _T(DEVICE_OUTPUT_FORMAT);
			state.deviceStateFilter = DEVICE_STATE_ACTIVE;


			state.hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
			if (SUCCEEDED(state.hr))
			{
				createDeviceEnumerator(&state);
			}
		}

		// Create a multimedia device enumerator.
		void createDeviceEnumerator(TGlobalState* state)
		{
			state->pEnum = NULL;
			state->hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
			(void**)&state->pEnum);
			if (SUCCEEDED(state->hr))
			{
				prepareDeviceEnumerator(state);
			}
		}

		// Prepare the device enumerator
		void prepareDeviceEnumerator(TGlobalState* state)
		{
			state->hr = state->pEnum->EnumAudioEndpoints(eRender, state->deviceStateFilter, &state->pDevices);
			if SUCCEEDED(state->hr)
			{
				enumerateOutputDevices(state);
			}
			state->pEnum->Release();
		}

		// Enumerate the output devices
		void enumerateOutputDevices(TGlobalState* state)
		{
			UINT count;
			state->pDevices->GetCount(&count);

			// If option is less than 1, list devices
			if (state->option < 1)
			{

				// Get default device
				IMMDevice* pDefaultDevice;
				state->hr = state->pEnum->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDefaultDevice);
				if (SUCCEEDED(state->hr))
				{

					state->hr = pDefaultDevice->GetId(&state->strDefaultDeviceID);

					// Iterate all devices
					for (int i = 1; i <= (int)count; i++)
					{
						state->hr = state->pDevices->Item(i - 1, &state->pCurrentDevice);
						if (SUCCEEDED(state->hr))
						{
							state->hr = printDeviceInfo(state->pCurrentDevice, i, state->pDeviceFormatStr, state->strDefaultDeviceID);

							IPropertyStore *pStore;
							state->hr = state->pCurrentDevice->OpenPropertyStore(STGM_READ, &pStore);
							if (SUCCEEDED(state->hr))
							{
								LPWSTR strID = NULL;
								state->hr = state->pCurrentDevice->GetId(&strID);
								if (SUCCEEDED(state->hr))
								{
									std::wstring friendlyName = getDeviceProperty(pStore, PKEY_Device_FriendlyName);
									std::wstring Desc = getDeviceProperty(pStore, PKEY_Device_DeviceDesc);
									std::wstring interfaceFriendlyName = getDeviceProperty(pStore, PKEY_DeviceInterface_FriendlyName);

									DWORD dwState;
									auto hr = state->pCurrentDevice->GetState(&dwState);
						
									this->AddDevice(gcnew String(friendlyName.c_str()), gcnew String(strID), (state->strDefaultDeviceID != '\0' && (wcscmp(state->strDefaultDeviceID, strID) == 0)));

								}

							}

							state->pCurrentDevice->Release();
						}
					}
				}
			}

			state->pDevices->Release();
		}

		HRESULT printDeviceInfo(IMMDevice* pDevice, int index, LPCWSTR outFormat, LPWSTR strDefaultDeviceID)
		{
			// Device ID
			LPWSTR strID = NULL;
			HRESULT hr = pDevice->GetId(&strID);
			if (!SUCCEEDED(hr))
			{
				return hr;
			}

			int deviceDefault = (strDefaultDeviceID != '\0' && (wcscmp(strDefaultDeviceID, strID) == 0));

			// Device state
			DWORD dwState;
			hr = pDevice->GetState(&dwState);
			if (!SUCCEEDED(hr))
			{
				return hr;
			}

			IPropertyStore *pStore;
			hr = pDevice->OpenPropertyStore(STGM_READ, &pStore);
			if (SUCCEEDED(hr))
			{
				std::wstring friendlyName = getDeviceProperty(pStore, PKEY_Device_FriendlyName);
				std::wstring Desc = getDeviceProperty(pStore, PKEY_Device_DeviceDesc);
				std::wstring interfaceFriendlyName = getDeviceProperty(pStore, PKEY_DeviceInterface_FriendlyName);

				if (SUCCEEDED(hr))
				{
					wprintf_s(outFormat,
					index,
					friendlyName.c_str(),
					dwState,
					deviceDefault,
					Desc.c_str(),
					interfaceFriendlyName.c_str(),
					strID
					);
					wprintf_s(_T("\n"));
				}

				pStore->Release();
			}
			return hr;
		}

		std::wstring getDeviceProperty(IPropertyStore* pStore, const PROPERTYKEY key)
		{
			PROPVARIANT prop;
			PropVariantInit(&prop);
			HRESULT hr = pStore->GetValue(key, &prop);
			if (SUCCEEDED(hr))
			{
				std::wstring result (prop.pwszVal);
				PropVariantClear(&prop);
				return result;
			}
			else
			{
				return std::wstring (L"");
			}
		}

		HRESULT SetDefaultAudioPlaybackDevice(LPCWSTR devID)
		{
			IPolicyConfigVista *pPolicyConfig;
			ERole reserved = eConsole;

			HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigVistaClient),
			NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID *)&pPolicyConfig);
			if (SUCCEEDED(hr))
			{
				hr = pPolicyConfig->SetDefaultEndpoint(devID, reserved);
				pPolicyConfig->Release();
			}
			return hr;
		}

		void invalidParameterHandler(const wchar_t* expression,
		   const wchar_t* function,
		   const wchar_t* file,
		   unsigned int line,
		   uintptr_t pReserved)
		{
			wprintf_s(_T("\nError: Invalid format_str.\n"));
			exit(1);
		}
	};
}

