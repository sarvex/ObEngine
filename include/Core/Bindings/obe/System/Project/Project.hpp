#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Project::Bindings
{
    void LoadFunctionGetProjectLocation(sol::state_view state);
    void LoadFunctionProjectExists(sol::state_view state);
    void LoadFunctionLoad(sol::state_view state);
    void LoadFunctionListProjects(sol::state_view state);
};
