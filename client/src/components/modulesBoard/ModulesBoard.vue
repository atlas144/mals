<template>
  <grid-layout :layout="layoutSettings.layout" :col-num="layoutSettings.columNumber" :row-height="layoutSettings.rowHeight" :margin="layoutSettings.margin" :is-draggable="layoutSettings.draggable" :is-resizable="layoutSettings.resizable" :vertical-compact="layoutSettings.compact" :responsive="layoutSettings.responsive" :use-css-transforms="layoutSettings.useCssTransforms" :breakpoints="layoutSettings.breakpoints" :cols="layoutSettings.columns">
    <grid-item v-for="module in modules" :key="module.i" :x="module.x" :y="module.y" :w='module.w' :min-w="module.minW" :h="module.h" :min-h="module.minH" :i="module.i" :drag-ignore-from="layoutSettings.preventDragFrom">
      <div class="moduleContainer">
        <ModuleHeader :name='module.i' />
        <component :is="module.identifier" />
      </div>
    </grid-item>
  </grid-layout>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";
import ModuleHeader from "./ModuleHeader.vue";
import ModuleProperties from "./ModuleProperties";
import TestModule from "./customModules/testModule/TestModule.vue";

@Options({
  components: {
    ModuleHeader,
    TestModule,
  },
})
export default class ModulesBoard extends Vue {
  public modules = [
    new ModuleProperties('Test module', 'TestModule', 3, 7),
  ];
  public layoutSettings = {
    layout: this.modules,
    columNumber: 12,
    rowHeight: 20,
    margin: [40, 40],
    isDraggable: true,
    isResizable: true,
    compact: true,
    responsive: true,
    useCssTransforms: true,
    breakpoints: {
      lg: 1200,
      md: 996,
      sm: 768,
      xs: 480,
      xxs: 0,
    },
    columns: {
      lg: 12,
      md: 9,
      sm: 6,
      xs: 3,
      xxs: 3,
    },
    preventDragFrom: 'a, button, input, select',
  };
}
</script>

<style>

label {
  display: block;
  padding: 12px 0 6px 0;
  font-weight: bold;
}

::placeholder {
  color: #1e5128;
  opacity: 0.6;
}

input, select, textarea, button {
  width: 100%;
  margin: 6px 0;
  padding: 12px;
  border-radius: 10px;
  box-sizing: border-box;
  font-family: OpenSauceTwoRegular;
  transition: 0.3s;
}

input[type=text], select, textarea {
  background-color: #f5ffdb;
  border: 2px solid #4e9f3d;
  color: #1e5128;
  resize: vertical;
}

input[type=submit], button {
  margin: 12px 0;
  padding: 10px;
  background-color: #4e9f3d;
  color: #f5ffdb;
  border: 2px solid #4e9f3d;
  font-size: 16px;
  font-weight: bold;
  cursor: pointer;
}

input[type=submit]:hover, button:hover {
  background-color: #1e5128;
  color: #4e9f3d;
}

.vue-resizable-handle {
  z-index: 5000;
  position: absolute;
  margin: 0 10px 10px 0;
  padding: 0 3px 3px 0;
  width: 20px;
  height: 20px;
  bottom: 0;
  right: 0;
  background: url('data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/Pg08IS0tIEdlbmVyYXRvcjogQWRvYmUgRmlyZXdvcmtzIENTNiwgRXhwb3J0IFNWRyBFeHRlbnNpb24gYnkgQWFyb24gQmVhbGwgKGh0dHA6Ly9maXJld29ya3MuYWJlYWxsLmNvbSkgLiBWZXJzaW9uOiAwLjYuMSAgLS0+DTwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+DTxzdmcgaWQ9IlVudGl0bGVkLVBhZ2UlMjAxIiB2aWV3Qm94PSIwIDAgNiA2IiBzdHlsZT0iYmFja2dyb3VuZC1jb2xvcjojZmZmZmZmMDAiIHZlcnNpb249IjEuMSINCXhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHhtbDpzcGFjZT0icHJlc2VydmUiDQl4PSIwcHgiIHk9IjBweCIgd2lkdGg9IjZweCIgaGVpZ2h0PSI2cHgiDT4NCTxnIG9wYWNpdHk9IjAuMzAyIj4NCQk8cGF0aCBkPSJNIDYgNiBMIDAgNiBMIDAgNC4yIEwgNCA0LjIgTCA0LjIgNC4yIEwgNC4yIDAgTCA2IDAgTCA2IDYgTCA2IDYgWiIgZmlsbD0iIzAwMDAwMCIvPg0JPC9nPg08L3N2Zz4=');
  filter: invert(86%) sepia(13%) saturate(387%) hue-rotate(43deg) brightness(112%) contrast(104%);
  background-position: bottom right;
  background-repeat: no-repeat;
  background-origin: content-box;
  box-sizing: border-box;
  cursor: se-resize;
}

.vue-grid-item.vue-grid-placeholder {
  background-color: #4e9f3d !important;
  border-radius: 20px;
}

.vue-grid-item:not(.vue-grid-placeholder) {
  background-color: #1e5128;
  color: #f5ffdb;
  transition: 0.3s;
  border: solid 2px #4e9f3d;
  border-radius: 20px;
}

.vue-grid-item.resizing {
  opacity: 0.9;
}

.moduleContainer {
  padding: 30px;
}
</style>