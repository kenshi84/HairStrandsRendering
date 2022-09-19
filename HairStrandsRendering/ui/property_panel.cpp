#include "property_panel.h"
#include "ui/imguiplugins/ImGuiFileDialog.h"

void PropertyPanel::render(SceneView* scene_view)
{
    // auto mesh = scene_view->get_mesh();
    auto render_param = scene_view->get_render_param();
  
    ImGui::Begin("Properties");

    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Button("Open Mesh"))
        {
            m_mesh_loading = true;
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File",
                                                    ".ply,.fbx,.obj,.off", "../Data/", 1, nullptr, ImGuiFileDialogFlags_Modal);
        }
        ImGui::SameLine(0, 5.0f);
        ImGui::Text(m_mesh_current_file.c_str());
    }

    if (ImGui::CollapsingHeader("Strands", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Button("Open Strands"))
        {
            m_strands_loading = true;
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File",
                                                    ".bin,.data", "../Data/", 1, nullptr, ImGuiFileDialogFlags_Modal);
        }
        ImGui::SameLine(0, 5.0f);
        ImGui::Text(m_strands_current_file.c_str());
    }
  
    if (ImGui::CollapsingHeader("Scene", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::ColorEdit3("Clear Color", (float*)&render_param->clear_color);
    }

    if (ImGui::CollapsingHeader("Mesh Properties") && render_param)
    {
        ImGui::ColorPicker3("Mesh Color", (float*)&render_param->mesh_color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
        ImGui::SliderFloat("Mesh Diffuse", &render_param->mesh_diffuse, 0.0f, 1.0f);
        ImGui::SliderFloat("Mesh Specular", &render_param->mesh_specular, 0.0f, 1.0f);
        ImGui::SliderFloat("Mesh Ambient", &render_param->mesh_ambient, 0.0f, 1.0f);
    }
  
    if (ImGui::CollapsingHeader("Strands Properties", ImGuiTreeNodeFlags_DefaultOpen) && render_param)
    {
        ImGui::ColorPicker3("Strs Color", (float*)&render_param->strands_color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
        ImGui::SliderInt("Strs Width", &render_param->strands_width, 1, 10);
        ImGui::SliderFloat("Strs Alpha", &render_param->strands_alpha, 0.0f, 1.0f);
        ImGui::SliderFloat("Strs Diffuse", &render_param->strands_diffuse, 0.0f, 1.0f);
        ImGui::SliderFloat("Strs Specular", &render_param->strands_specular, 0.0f, 1.0f);
        ImGui::SliderFloat("Strs Ambient", &render_param->strands_ambient, 0.0f, 1.0f);
    }

    if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::SliderFloat("Strength", &scene_view->get_lights()->m_strength, 0.f, 1.f);
        ImGui::SliderFloat3("Rot", scene_view->get_lights()->m_rot, 0.f, 3.1415f);
    }
    
    if (ImGui::CollapsingHeader("Shadow Properties", ImGuiTreeNodeFlags_DefaultOpen) && render_param)
    {
        ImGui::SliderFloat("Mesh Self", &render_param->mesh_self_shadow, 0.0f, 0.95f);
        ImGui::SliderFloat("Mesh Strs", &render_param->mesh_strands_shadow, 0.0f, 0.95f);
        ImGui::SliderFloat("Strs Self", &render_param->strands_self_shadow, 0.0f, 0.95f);
        ImGui::SliderFloat("Strs Mesh", &render_param->strands_mesh_shadow, 0.0f, 0.95f);
    }
  
    ImGui::End();
  
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string file_name = ImGuiFileDialog::Instance()->GetFilePathName();
            if(m_mesh_loading)
            {
                m_mesh_current_file = file_name.substr(file_name.find_last_of("/\\") + 1);
                m_mesh_loading = false;
                m_mesh_load_callback(file_name);
            }
            else if (m_strands_loading)
            {
                m_strands_current_file = file_name.substr(file_name.find_last_of("/\\") + 1);
                m_strands_loading = false;
                m_strands_load_callback(file_name);
            }
            
        }
        ImGuiFileDialog::Instance()->Close();
    }
}