#include "WinForm.h"
#include "Interpreter.h"
#include "Equation.h"
#include <msclr/marshal_cppstd.h>


string resultRecord = "";

System::Void EM::WinForm::���J�ɮ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->OFD->ShowDialog();
	string path = msclr::interop::marshal_as< std::string >(this->OFD->FileName);
	
	loadVars(path);
	this->listView1->Items->Clear();
	for (auto it = vars.begin(); it != vars.end(); it++) {
		ListViewItem^ lvi = gcnew ListViewItem();
		lvi->Text = gcnew String(it->first.c_str());
		lvi->SubItems->Add(gcnew String(it->second.type.c_str()));
		if (it->second.type == "Vector") {
			lvi->SubItems->Add(gcnew String(((Vector*)(it->second.data))->getSizeInfo().c_str()));
			lvi->SubItems->Add(gcnew String(((Vector*)(it->second.data))->ToString().c_str()));
		}
		else if (it->second.type == "Matrix") {
			lvi->SubItems->Add(gcnew String(((Matrix*)(it->second.data))->getSizeInfo().c_str()));
			lvi->SubItems->Add(gcnew String(((Matrix*)(it->second.data))->ToString().c_str()));
		}
		this->listView1->Items->Add(lvi);
	}
}

System::Void EM::WinForm::WinForm_Load(System::Object^  sender, System::EventArgs^  e) {
	//Equation eq("x^2+x-2*x^0.5");

	//std::cout << "guo";
}

System::Void EM::WinForm::cmdBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ ex) {

	if (ex->KeyChar == '\r') {
		String^ f = this->cmdBox->Lines[cmdBox->Lines->Length - 2];
		String^ result = getResultStr(f);
		this->cmdBox->SelectionColor = Color::AntiqueWhite;
		resultRecord += msclr::interop::marshal_as< std::string >(result);
		this->cmdBox->AppendText(result);
		this->cmdBox->SelectionColor = this->cmdBox->ForeColor;
	}
}
System::Void EM::WinForm::saveResultsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->SFD->ShowDialog();
	string path = msclr::interop::marshal_as< std::string >(this->SFD->FileName);
	std::ofstream fout(path);
	fout << resultRecord;
	fout.close();
}

System::Void EM::WinForm::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	clearMap();
	vCounter = 0;
	mCounter = 0;
	this->listView1->Items->Clear();
}

System::Void EM::WinForm::loadEqualToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->OFD->ShowDialog();
	string path = msclr::interop::marshal_as< std::string >(this->OFD->FileName);
	vector<string> display = loadEquations(path);
	this->EqtListBox->Items->Clear();
	for (int i = 0; i < display.size(); ++i) {
		this->EqtListBox->Items->Add(gcnew String(display[i].c_str()));
	}
}
