#include <wx/wx.h>
#include <wx/listctrl.h>

class ToDoApp : public wxApp
{
public:
    virtual bool OnInit();
};

class ToDoFrame : public wxFrame
{
public:
    ToDoFrame();

private:
    void OnAdd(wxCommandEvent& event);
    void OnRemove(wxCommandEvent& event);

    wxListCtrl* m_listCtrl;
    wxTextCtrl* m_textCtrl;
};

wxIMPLEMENT_APP(ToDoApp);

bool ToDoApp::OnInit()
{
    ToDoFrame* frame = new ToDoFrame();
    frame->Show(true);
    return true;
}

ToDoFrame::ToDoFrame()
    : wxFrame(NULL, wxID_ANY, "To-Do List", wxDefaultPosition, wxSize(400, 300))
{
    wxPanel* panel = new wxPanel(this);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    m_listCtrl = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    m_listCtrl->InsertColumn(0, "Tasks", wxLIST_FORMAT_LEFT, 300);

    m_textCtrl = new wxTextCtrl(panel, wxID_ANY);

    wxButton* btnAdd = new wxButton(panel, wxID_ANY, "Add");
    wxButton* btnRemove = new wxButton(panel, wxID_ANY, "Remove");

    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(btnAdd);
    hbox->Add(btnRemove);

    vbox->Add(m_listCtrl, 1, wxEXPAND | wxALL, 10);
    vbox->Add(m_textCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    vbox->Add(hbox, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

    panel->SetSizer(vbox);

    btnAdd->Bind(wxEVT_BUTTON, &ToDoFrame::OnAdd, this);
    btnRemove->Bind(wxEVT_BUTTON, &ToDoFrame::OnRemove, this);
}

void ToDoFrame::OnAdd(wxCommandEvent& event)
{
    wxString task = m_textCtrl->GetValue();
    if (!task.IsEmpty())
    {
        m_listCtrl->InsertItem(m_listCtrl->GetItemCount(), task);
        m_textCtrl->Clear();
    }
}

void ToDoFrame::OnRemove(wxCommandEvent& event)
{
    long itemIndex = m_listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex != wxNOT_FOUND)
    {
        m_listCtrl->DeleteItem(itemIndex);
    }
}
