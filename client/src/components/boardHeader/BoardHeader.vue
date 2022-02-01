<template>
  <div id="header">
    <div id="logo">{{logo}}</div>
    <div id="description">
      {{description1Line}}<br>
      {{description2Line}}
    </div>
  </div>
</template>

<script lang="ts">
import { Vue } from "vue-class-component";

export default class BoardHeader extends Vue {
  public logo = 'M.A.L.S.';
  public description1Line = 'Control board of';
  public description2Line = 'mobile robotic system M.A.L.S.';
}
</script>

<style scoped>
#header {
	width: 100%;
  background-color: #1e5128;
  border-bottom: 4px solid #4e9f3d;
}

#logo {
  display: inline-block;
  padding: 15px 60px;
	font-family: 'KarlaBoldStencil';
	font-size: 56px;
  font-weight: bold;
}

#description {
  padding: 26px 60px;
  float: right;
  text-align: right;
	font-size: 18px;
  font-weight: bold;
}
</style>