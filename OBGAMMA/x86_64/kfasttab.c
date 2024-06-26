/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__kfasttab
#define _nrn_initial _nrn_initial__kfasttab
#define nrn_cur _nrn_cur__kfasttab
#define _nrn_current _nrn_current__kfasttab
#define nrn_jacob _nrn_jacob__kfasttab
#define nrn_state _nrn_state__kfasttab
#define _net_receive _net_receive__kfasttab 
#define rates rates__kfasttab 
#define states states__kfasttab 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define gkbar _p[0]
#define gkbar_columnindex 0
#define ik _p[1]
#define ik_columnindex 1
#define n _p[2]
#define n_columnindex 2
#define k _p[3]
#define k_columnindex 3
#define ek _p[4]
#define ek_columnindex 4
#define Dn _p[5]
#define Dn_columnindex 5
#define Dk _p[6]
#define Dk_columnindex 6
#define _g _p[7]
#define _g_columnindex 7
#define _ion_ek	*_ppvar[0]._pval
#define _ion_ik	*_ppvar[1]._pval
#define _ion_dikdv	*_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_rates(void);
 static void _hoc_table_tabktau(void);
 static void _hoc_tabktau(void);
 static void _hoc_table_tabkinf(void);
 static void _hoc_tabkinf(void);
 static void _hoc_table_tabntau(void);
 static void _hoc_tabntau(void);
 static void _hoc_table_tabninf(void);
 static void _hoc_tabninf(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_kfasttab", _hoc_setdata,
 "rates_kfasttab", _hoc_rates,
 "table_tabktau_kfasttab", _hoc_table_tabktau,
 "tabktau_kfasttab", _hoc_tabktau,
 "table_tabkinf_kfasttab", _hoc_table_tabkinf,
 "tabkinf_kfasttab", _hoc_tabkinf,
 "table_tabntau_kfasttab", _hoc_table_tabntau,
 "tabntau_kfasttab", _hoc_tabntau,
 "table_tabninf_kfasttab", _hoc_table_tabninf,
 "tabninf_kfasttab", _hoc_tabninf,
 0, 0
};
#define table_tabktau table_tabktau_kfasttab
#define tabktau tabktau_kfasttab
#define table_tabkinf table_tabkinf_kfasttab
#define tabkinf tabkinf_kfasttab
#define table_tabntau table_tabntau_kfasttab
#define tabntau tabntau_kfasttab
#define table_tabninf table_tabninf_kfasttab
#define tabninf tabninf_kfasttab
 extern double table_tabktau( );
 extern double tabktau( double );
 extern double table_tabkinf( );
 extern double tabkinf( double );
 extern double table_tabntau( );
 extern double tabntau( double );
 extern double table_tabninf( );
 extern double tabninf( double );
 /* declare global and static user variables */
#define ktau ktau_kfasttab
 double ktau = 0;
#define kinf kinf_kfasttab
 double kinf = 0;
#define ntau ntau_kfasttab
 double ntau = 0;
#define ninf ninf_kfasttab
 double ninf = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "gkbar_kfasttab", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "ntau_kfasttab", "ms",
 "ktau_kfasttab", "ms",
 "gkbar_kfasttab", "mho/cm2",
 "ik_kfasttab", "mA/cm2",
 0,0
};
 static double delta_t = 1;
 static double k0 = 0;
 static double n0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "ninf_kfasttab", &ninf_kfasttab,
 "kinf_kfasttab", &kinf_kfasttab,
 "ntau_kfasttab", &ntau_kfasttab,
 "ktau_kfasttab", &ktau_kfasttab,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"kfasttab",
 "gkbar_kfasttab",
 0,
 "ik_kfasttab",
 0,
 "n_kfasttab",
 "k_kfasttab",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 8, _prop);
 	/*initialize range parameters*/
 	gkbar = 0.12;
 	_prop->param = _p;
 	_prop->param_size = 8;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _kfasttab_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 8, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 kfasttab /home/jv/OBGAMMA/kfasttab.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "HH fast potassium channel with FUNCTION_TABLEs";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 
static void* _ptable_tabktau = (void*)0;
 
static void* _ptable_tabkinf = (void*)0;
 
static void* _ptable_tabntau = (void*)0;
 
static void* _ptable_tabninf = (void*)0;
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   Dn = ( ninf - n ) / ntau ;
   Dk = ( kinf - k ) / ktau ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ntau )) ;
 Dk = Dk  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ktau )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ntau)))*(- ( ( ( ninf ) ) / ntau ) / ( ( ( ( - 1.0 ) ) ) / ntau ) - n) ;
    k = k + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ktau)))*(- ( ( ( kinf ) ) / ktau ) / ( ( ( ( - 1.0 ) ) ) / ktau ) - k) ;
   }
  return 0;
}
 
double tabninf (  double _lv ) {
 double _arg[1];
 _arg[0] = _lv;
 return hoc_func_table(_ptable_tabninf, 1, _arg);
 }
/*  }
  */
 
static void _hoc_tabninf(void) {
  double _r;
   _r =  tabninf (  *getarg(1) );
 hoc_retpushx(_r);
}
 double table_tabninf ( ) {
	hoc_spec_table(&_ptable_tabninf, 1);
	return 0.;
}
 
static void _hoc_table_tabninf(void) {
  double _r;
   _r =  table_tabninf (  );
 hoc_retpushx(_r);
}
 
double tabntau (  double _lv ) {
 double _arg[1];
 _arg[0] = _lv;
 return hoc_func_table(_ptable_tabntau, 1, _arg);
 }
/*  }
  */
 
static void _hoc_tabntau(void) {
  double _r;
   _r =  tabntau (  *getarg(1) );
 hoc_retpushx(_r);
}
 double table_tabntau ( ) {
	hoc_spec_table(&_ptable_tabntau, 1);
	return 0.;
}
 
static void _hoc_table_tabntau(void) {
  double _r;
   _r =  table_tabntau (  );
 hoc_retpushx(_r);
}
 
double tabkinf (  double _lv ) {
 double _arg[1];
 _arg[0] = _lv;
 return hoc_func_table(_ptable_tabkinf, 1, _arg);
 }
/*  }
  */
 
static void _hoc_tabkinf(void) {
  double _r;
   _r =  tabkinf (  *getarg(1) );
 hoc_retpushx(_r);
}
 double table_tabkinf ( ) {
	hoc_spec_table(&_ptable_tabkinf, 1);
	return 0.;
}
 
static void _hoc_table_tabkinf(void) {
  double _r;
   _r =  table_tabkinf (  );
 hoc_retpushx(_r);
}
 
double tabktau (  double _lv ) {
 double _arg[1];
 _arg[0] = _lv;
 return hoc_func_table(_ptable_tabktau, 1, _arg);
 }
/*  }
  */
 
static void _hoc_tabktau(void) {
  double _r;
   _r =  tabktau (  *getarg(1) );
 hoc_retpushx(_r);
}
 double table_tabktau ( ) {
	hoc_spec_table(&_ptable_tabktau, 1);
	return 0.;
}
 
static void _hoc_table_tabktau(void) {
  double _r;
   _r =  table_tabktau (  );
 hoc_retpushx(_r);
}
 
static int  rates (  double _lv ) {
   ninf = tabninf ( _threadargscomma_ _lv ) ;
   ntau = tabntau ( _threadargscomma_ _lv ) ;
   kinf = tabkinf ( _threadargscomma_ _lv ) ;
   ktau = tabktau ( _threadargscomma_ _lv ) ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   _r = 1.;
 rates (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
     _ode_spec1 ();
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 ();
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  k = k0;
  n = n0;
 {
   rates ( _threadargscomma_ v ) ;
   n = ninf ;
   k = kinf ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  ek = _ion_ek;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ik = gkbar * n * n * k * ( v - ek ) ;
   }
 _current += ik;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  ek = _ion_ek;
 _g = _nrn_current(_v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  ek = _ion_ek;
 { error =  states();
 if(error){fprintf(stderr,"at line 44 in file kfasttab.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = n_columnindex;  _dlist1[0] = Dn_columnindex;
 _slist1[1] = k_columnindex;  _dlist1[1] = Dk_columnindex;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/home/jv/OBGAMMA/kfasttab.mod";
static const char* nmodl_file_text = 
  "TITLE HH fast potassium channel with FUNCTION_TABLEs\n"
  ": Hodgkin - Huxley potassium channel using the data given in\n"
  ": US Bhalla and JM Bower, J. Neurophysiol. 69:1948-1983 (1993)\n"
  ": Needs the files tabchannels.dat and tabchannels.hoc\n"
  ": Andrew Davison, The Babraham Institute, 1998.\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX kfasttab\n"
  "	USEION k READ ek WRITE ik\n"
  "	RANGE gkbar, ik\n"
  "	GLOBAL ninf, kinf, ntau, ktau\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "}\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "PARAMETER {\n"
  "	v (mV)\n"
  "	dt (ms)\n"
  "	gkbar= 0.120 (mho/cm2) <0,1e9>\n"
  "	ek = -70 (mV)\n"
  "}\n"
  "STATE {\n"
  "	n k\n"
  "}\n"
  "ASSIGNED {\n"
  "	ik (mA/cm2)\n"
  "	ninf\n"
  "	kinf\n"
  "	ntau (ms)\n"
  "	ktau (ms)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	rates(v)\n"
  "	n = ninf\n"
  "	k = kinf\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	ik = gkbar*n*n*k*(v - ek)\n"
  "}\n"
  "\n"
  "DERIVATIVE states {\n"
  "	rates(v)\n"
  "	n' = (ninf - n)/ntau\n"
  "	k' = (kinf - k)/ktau\n"
  "}\n"
  "\n"
  "FUNCTION_TABLE tabninf(v(mV))\n"
  "FUNCTION_TABLE tabntau(v(mV)) (ms)\n"
  "FUNCTION_TABLE tabkinf(v(mV))\n"
  "FUNCTION_TABLE tabktau(v(mV)) (ms)\n"
  "\n"
  "PROCEDURE rates(v(mV)) {\n"
  "	ninf = tabninf(v)\n"
  "	ntau = tabntau(v) \n"
  "	kinf = tabkinf(v)\n"
  "	ktau = tabktau(v)\n"
  "}\n"
  ;
#endif
