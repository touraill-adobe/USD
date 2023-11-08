//
// Copyright 2023 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
////////////////////////////////////////////////////////////////////////

/* ************************************************************************** */
/* ** This file is generated by a script.  Do not edit directly.  Edit     ** */
/* ** defs.py or the (*)Schema.template.cpp files to make changes.         ** */
/* ************************************************************************** */

#include "{{ INCLUDE_PATH }}/{{ FILE_NAME }}.h"
#include "pxr/imaging/hd/retainedDataSource.h"
{% if IMPL_OTHER_SCHEMA_INCLUDES is defined -%}
{% for t in IMPL_OTHER_SCHEMA_INCLUDES -%}
#include "pxr/imaging/hd/{{ t }}Schema.h"
{% endfor %}{% endif %}
#include "pxr/base/trace/trace.h"
{% block additional_includes %}{% endblock %}

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS({{SCHEMA_NAME}}SchemaTokens,
    {{ SCHEMA_NAME|upper }}_SCHEMA_TOKENS);

{% block additional_methods %}{% endblock additional_methods %}
{% if MEMBERS is defined %}{% for name, type_name in MEMBERS %}
{{ type_name}}{% if not type_name.endswith('Schema') %}Handle{% endif %}
{{ SCHEMA_NAME }}Schema::Get{{ name|capitalizeFirst }}()
{
{%- if ACCCESSOR_IMPL_OVERRIDES is defined and name in ACCCESSOR_IMPL_OVERRIDES %}
    // overriden definition from {{ ACCCESSOR_IMPL_OVERRIDES[name] }}
{% include ACCCESSOR_IMPL_OVERRIDES[name] %}{% else %}
    return {% if type_name.endswith('Schema') %}{{ type_name }}({% endif %}_GetTypedDataSource<{{type_name | underlyingDataSource}}>(
        {{SCHEMA_NAME}}SchemaTokens->{{ name }}){% if type_name.endswith('Schema') %}){% endif %};{% endif %}
}
{% endfor %}
/*static*/
HdContainerDataSourceHandle
{{ SCHEMA_NAME }}Schema::BuildRetained(
{%- for name, type_name in MEMBERS %}
        const {{type_name | underlyingDataSource}}Handle &{{ name }}{%if loop.last == False %},{% endif %}{% endfor %}
)
{
    TfToken _names[{{MEMBERS|length}}];
    HdDataSourceBaseHandle _values[{{MEMBERS|length}}];

    size_t _count = 0;
{%- for name, type_name in MEMBERS %}
    if ({{name}}) {
        _names[_count] = {{SCHEMA_NAME}}SchemaTokens->{{name}};
        _values[_count++] = {{name}};
    }
{% endfor %}
    return HdRetainedContainerDataSource::New(_count, _names, _values);
}
{% endif %}
{%- if GENERIC_BUILD_RETAINED is defined and GENERIC_BUILD_RETAINED %}
/*static*/
HdContainerDataSourceHandle
{{SCHEMA_NAME}}Schema::BuildRetained(
    const size_t count,
    const TfToken * const names,
    const HdDataSourceBaseHandle * const values)
{
    return HdRetainedContainerDataSource::New(count, names, values);
}
{% endif %}
{% if SCHEMA_TOKEN is defined %}/*static*/
{{ SCHEMA_NAME }}Schema
{{ SCHEMA_NAME }}Schema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return {{ SCHEMA_NAME }}Schema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                {{SCHEMA_NAME}}SchemaTokens->{{SCHEMA_TOKEN}}))
        : nullptr);
}
{% endif -%}

{% if SCHEMA_TOKEN is defined %}
/*static*/
const TfToken &
{{ SCHEMA_NAME }}Schema::GetSchemaToken()
{
    return {{SCHEMA_NAME}}SchemaTokens->{{SCHEMA_TOKEN}};
}
{% endif -%}

{% if DEFAULT_LOCATOR is defined %}
/*static*/
const HdDataSourceLocator &
{{ SCHEMA_NAME }}Schema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(
    {%- for t in DEFAULT_LOCATOR %}
        {%if t is string %}{{SCHEMA_NAME}}SchemaTokens->{{ t }}{% else %}{{ t[0] }}SchemaTokens->{{ t[1] }}{% endif %}{%if loop.last == False %},{% endif %}{% endfor %}
    );
    return locator;
} {% endif -%}{# ------------------------------------------------------------ #}

{%- if ADD_LOCATOR_FOR_EACH_MEMBER is defined and ADD_LOCATOR_FOR_EACH_MEMBER %}

{% for name, type_name in MEMBERS %}
/*static*/
const HdDataSourceLocator &
{{ SCHEMA_NAME }}Schema::Get{{ name |capitalizeFirst  }}Locator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            {{SCHEMA_NAME}}SchemaTokens->{{name}});
    return locator;
}
{% endfor %}{% endif -%}{# ------------------------------------------------------------ #}

{%- if STATIC_LOCATOR_ACCESSORS is defined %}{% for entry in STATIC_LOCATOR_ACCESSORS %}
/*static*/
const HdDataSourceLocator &
{{ SCHEMA_NAME }}Schema::Get{{entry[0]}}Locator()
{
    static const HdDataSourceLocator locator(
    {%- for t in entry[1] %}
        {%if t is string %}{{SCHEMA_NAME}}SchemaTokens->{{ t }}{% else %}{{ t[0] }}SchemaTokens->{{ t[1] }}{% endif %}{%if loop.last == False %},{% endif %}{% endfor %}
    );
    return locator;
}
{% endfor %}
{% endif -%}
{# -------------------------------------------------------------- #}
{%- if STATIC_TOKEN_DATASOURCE_BUILDERS is defined %}{% for entry in STATIC_TOKEN_DATASOURCE_BUILDERS %}

/*static*/
HdTokenDataSourceHandle
{{ SCHEMA_NAME }}Schema::Build{{entry[0]|capitalize}}DataSource(
    const TfToken &{{entry[0]|lower}})
{
{% for token in entry[1] %}    if ({{entry[0]|lower}} == {{SCHEMA_NAME}}SchemaTokens->{{token}}) {
        static const HdRetainedTypedSampledDataSource<TfToken>::Handle ds =
            HdRetainedTypedSampledDataSource<TfToken>::New({{entry[0]|lower}});
        return ds;
    }
{% endfor %}
    // fallback for unknown token
    return HdRetainedTypedSampledDataSource<TfToken>::New({{entry[0]|lower}});
}
{% endfor %}{% endif -%}
{% if MEMBERS is defined %}{% for name, type_name in MEMBERS %}
{{ SCHEMA_NAME }}Schema::Builder &
{{ SCHEMA_NAME }}Schema::Builder::Set{{ name|capitalizeFirst }}(
    const {{ type_name | underlyingDataSource}}Handle &{{name}})
{
    _{{name}} = {{name}};
    return *this;
}
{% endfor %}
HdContainerDataSourceHandle
{{ SCHEMA_NAME }}Schema::Builder::Build()
{
    return {{ SCHEMA_NAME }}Schema::BuildRetained(
{%- for name, type_name in MEMBERS %}
        _{{ name }}{%if loop.last == False %},{% endif %}{% endfor %}
    );
}

{% endif %}
PXR_NAMESPACE_CLOSE_SCOPE
