/**
 *  @file PDSS_HKFT.h
 *    Declarations for the class PDSS_HKFT (pressure dependent standard state)
 *    which handles calculations for a single species in a phase using the
 *    HKFT standard state
 *    (see class \link Cantera::PDSS_HKFT PDSS_HKFT\endlink).
 */
/*  $Author$
 *  $Date$
 *  $Revision$
 *
 * 
 */

#ifndef CT_PDSS_HKFT_H
#define CT_PDSS_HKFT_H
#include "ct_defs.h"



class WaterPropsIAPWS;
#include "PDSS.h"

namespace Cantera {
  class XML_Node;
  class VPStandardState;
  class PDSS_Water;
  class WaterProps;

 
  //! Class for pressure dependent standard states corresponding to 
  //!  ionic solutes in electrolyte water.
  /*!
   *
   * Virtual base class for calculation of the
   * pressure dependent standard state for a single species
   * 
   * Class %PDSS is the base class
   * for a family of classes that compute properties of a set of
   * species in their standard states at a range of temperatures
   * and pressures. The independent variables for this object
   * are temperature and pressure.
   * The class may mave a reference to a SpeciesThermo object
   * which handles the calculation of the reference state temperature
   * behavior of a subset of species.
   *
   * This class is analagous to the SpeciesThermoInterpType
   * class, except that the standard state inherently incorporates
   * the pressure dependence.
   *
   * The class operates on a setState temperature and pressure basis.
   * It only recalculates the standard state when the setState functions
   * for temperature and pressure are called
   *
   */
  class PDSS_HKFT : public PDSS {

  public:
   /**
     * @name  Constructors
     * @{
     */

   //! Constructor that initializes the object by examining the XML entries
    //! from the ThermoPhase object
    /*!
     *  This function calls the constructPDSS member function.
     * 
     *  @param tp        Pointer to the ThermoPhase object pertaining to the phase
     *  @param spindex   Species index of the species in the phase
     */
    PDSS_HKFT(VPStandardStateTP *tp, int spindex);

    //! Copy Constructor
    /*!
     * @param b object to be copied
     */
    PDSS_HKFT(const PDSS_HKFT &b);

    //! Assignment operator
    /*!
     * @param b Object to be copied
     */
    PDSS_HKFT& operator=(const PDSS_HKFT&b);

    //! Constructor that initializes the object by examining the input file
    //! of the ThermoPhase object
    /*!
     *  This function calls the constructPDSSFile member function.
     * 
     *  @param vptp_ptr  Pointer to the ThermoPhase object pertaining to the phase
     *  @param spindex   Species index of the species in the phase
     *  @param inputFile String name of the input file
     *  @param id        String name of the phase in the input file. The default
     *                   is the empty string, in which case the first phase in the
     *                   file is used.
     */
    PDSS_HKFT(VPStandardStateTP *vptp_ptr, int spindex,
	      std::string inputFile, std::string id = "");

    //! Constructor that initializes the object by examining the input file
    //! of the ThermoPhase object
    /*!
     *  This function calls the constructPDSSXML member function.
     * 
     *  @param vptp_ptr    Pointer to the ThermoPhase object pertaining to the phase
     *  @param spindex     Species index of the species in the phase
     *  @param speciesNode Reference to the species XML tree.
     *  @param phaseRef    Reference to the XML tree containing the phase information.
     *  @param spInstalled Boolean indicating whether the species is installed yet
     *                     or not.
     */
    PDSS_HKFT(VPStandardStateTP *vptp_ptr, int spindex, const XML_Node& speciesNode,
	      const XML_Node& phaseRef, bool spInstalled);

    //! Destructor for the phase
    virtual ~PDSS_HKFT();

    //! Duplicator
    virtual PDSS *duplMyselfAsPDSS() const;
   
    /**
     * @}   
     * @name  Utilities  
     * @{
     */
    virtual int pdssType() const { return -1; }

    /**
     * @} 
     * @name  Molar Thermodynamic Properties of the Species Standard State
     *        in the Solution
     * @{
     */
    
    /**
     * @} 
     * @name  Molar Thermodynamic Properties of the Solution --------------
     * @{
     */

    //! Return the molar enthalpy in units of J kmol-1
    /*!
     * Returns the species standard state enthalpy in J kmol-1 at the
     * current temperature and pressure.
     *
     * @return returns the species standard state enthalpy in  J kmol-1
     */
    virtual doublereal enthalpy_mole() const;

    //! Return the standard state molar enthalpy divided by RT
    /*!
     * Returns the species standard state enthalpy divided by RT at the
     * current temperature and pressure.
     *
     * @return returns the species standard state enthalpy in unitless form
     */
    virtual doublereal enthalpy_RT() const;

    //! Return the molar internal Energy in units of J kmol-1
    /*!
     * Returns the species standard state internal Energy in J kmol-1 at the
     * current temperature and pressure.
     *
     * @return returns the species standard state internal Energy in  J kmol-1
     */
    virtual doublereal intEnergy_mole() const;

    //! Return the molar entropy in units of J kmol-1 K-1
    /*!
     * Returns the species standard state entropy in J kmol-1 K-1 at the
     * current temperature and pressure.
     *
     * @return returns the species standard state entropy in J kmol-1 K-1
     */
    virtual doublereal entropy_mole() const;

    //! Return the molar gibbs free energy in units of J kmol-1
    /*!
     * Returns the species standard state gibbs free energy in J kmol-1 at the
     * current temperature and pressure.
     *
     * @return returns the species standard state gibbs free energy in  J kmol-1
     */
    virtual doublereal gibbs_mole() const;

    //! Return the molar const pressure heat capacity in units of J kmol-1 K-1
    /*!
     * Returns the species standard state Cp in J kmol-1 K-1 at the
     * current temperature and pressure.
     *
     * @return returns the species standard state Cp in J kmol-1 K-1
     */
    virtual doublereal cp_mole() const;

    //! Return the molar const volume heat capacity in units of J kmol-1 K-1
    /*!
     * Returns the species standard state Cv in J kmol-1 K-1 at the
     * current temperature and pressure.
     *
     * @return returns the species standard state Cv in J kmol-1 K-1
     */
    virtual doublereal cv_mole() const;

    //! Return the molar volume at standard state
    /*!
     * Returns the species standard state molar volume at the
     * current temperature and pressure
     *
     * @return returns the standard state molar volume divided by R
     *             units are m**3 kmol-1.
     */
    virtual doublereal molarVolume() const;

    //! Return the standard state density at standard state
    /*!
     * Returns the species standard state density at the
     * current temperature and pressure
     *
     * @return returns the standard state density
     *             units are kg m-3
     */
    virtual doublereal density() const;

    /**
     * @} 
     * @name Properties of the Reference State of the Species
     *       in the Solution 
     * @{
     */


    //! Return the reference pressure for this phase.
    doublereal refPressure() const {
      return m_p0;
    }

    //! Return the molar gibbs free energy divided by RT at reference pressure
    /*!
     * Returns the species reference state gibbs free energy divided by RT at the
     * current temperature.
     *
     * @return returns the reference state gibbs free energy divided by RT
     */
    virtual doublereal gibbs_RT_ref() const;

    //! Return the molar enthalpy divided by RT at reference pressure
    /*!
     * Returns the species reference state enthalpy divided by RT at the
     * current temperature.
     *
     * @return returns the reference state enthalpy divided by RT
     */
    virtual doublereal enthalpy_RT_ref() const;

    //! Return the molar entropy divided by R at reference pressure
    /*!
     * Returns the species reference state entropy divided by R at the
     * current temperature.
     *
     * @return returns the reference state entropy divided by R
     */
    virtual doublereal entropy_R_ref() const;

    //! Return the molar heat capacity divided by R at reference pressure
    /*!
     * Returns the species reference state heat capacity divided by R at the
     * current temperature.
     *
     * @return returns the reference state heat capacity divided by R
     */
    virtual doublereal cp_R_ref() const;

    //! Return the molar volume at reference pressure
    /*!
     * Returns the species reference state molar volume at the
     * current temperature.
     *
     * @return returns the reference state molar volume divided by R
     *             units are m**3 kmol-1.
     */
    virtual doublereal molarVolume_ref() const;

    /**
     * @}
     *  @name Mechanical Equation of State Properties 
     * @{
     */

     //! Returns the pressure (Pa)
    virtual doublereal pressure() const;

    //! Sets the pressure in the object
    /*!
     * Currently, this sets the pressure in the PDSS object.
     * It is indeterminant what happens to the owning VPStandardStateTP
     * object and to the VPSSMgr object.
     *
     * @param   pres   Pressure to be set (Pascal)
     */
    virtual void setPressure(doublereal pres);

    //! Set the internal temperature
    /*!
     * @param temp Temperature (Kelvin)
     */
    virtual void setTemperature(doublereal temp);

    //! Return the current storred temperature
    doublereal temperature() const;
 
    //! Set the internal temperature and pressure
    /*!
     * @param  temp     Temperature (Kelvin)
     * @param  pres     pressure (Pascals)
     */
    virtual void setState_TP(doublereal temp, doublereal pres);

    /**
     * @}
     *  @name  Miscellaneous properties of the standard state
     * @{
     */ 

    /// critical temperature 
    virtual doublereal critTemperature() const;
 
    /// critical pressure
    virtual doublereal critPressure() const;
        
    /// critical density
    virtual doublereal critDensity() const;
     
    /**
     * @}
     *  @name  Initialization of the Object
     * @{
     */
    
    //! Initialization routine for all of the shallow pointers
    /*!
     *  This is a cascading call, where each level should call the
     *  the parent level.
     *
     *  The initThermo() routines get called before the initThermoXML() routines
     *  from the constructPDSSXML() routine.
     *
     *
     *  Calls initPtrs();
     */
    virtual void initThermo();

    //! Initialization of a PDSS object using an
    //! input XML file.
    /*!
     *
     * This routine is a precursor to constructPDSSXML(XML_Node*)
     * routine, which does most of the work.
     *
     * @param vptp_ptr    Pointer to the Variable pressure %ThermoPhase object
     *                    This object must have already been malloced.
     *
     * @param spindex     Species index within the phase
     *
     * @param inputFile   XML file containing the description of the
     *                    phase
     *
     * @param id          Optional parameter identifying the name of the
     *                    phase. If none is given, the first XML
     *                    phase element will be used.
     */
    void constructPDSSFile(VPStandardStateTP *vptp_ptr, int spindex, 
			   std::string inputFile, std::string id);

    //!  Initialization of a PDSS object using an xml tree
    /*!
     * This routine is a driver for the initialization of the
     * object.
     * 
     *   basic logic:
     *       initThermo()                 (cascade)
     *       getStuff from species Part of XML file
     *       initThermoXML(phaseNode)      (cascade)
     * 
     * @param vptp_ptr   Pointer to the Variable pressure %ThermoPhase object
     *                   This object must have already been malloced.
     *
     * @param spindex    Species index within the phase
     *
     * @param speciesNode XML Node containing the species information
     *
     * @param phaseNode  Reference to the phase Information for the phase
     *                   that owns this species.
     *
     * @param spInstalled  Boolean indicating whether the species is 
     *                     already installed.
     */
    void constructPDSSXML(VPStandardStateTP *vptp_ptr, int spindex, 
			  const XML_Node& speciesNode, 
			  const XML_Node& phaseNode, bool spInstalled);

    //! Initialization routine for the PDSS object based on the phaseNode
    /*!
     *  This is a cascading call, where each level should call the
     *  the parent level.
     *
     * @param phaseNode  Reference to the phase Information for the phase
     *                   that owns this species.
     *
     * @param id         Optional parameter identifying the name of the
     *                   phase. If none is given, the first XML
     *                   phase element will be used.
     */
    virtual void initThermoXML(const XML_Node& phaseNode, std::string id);

    //@}

 
  private:

    //! Main routine that actually calculates the gibbs free energy difference 
    //! between the reference state at Tr, Pr and T,P
    /*!
     *  This is eEqn. 59 in Johnson et al. (1992).
     *
     */
    double deltaG() const;

    //! Main routine that actually calculates the entropy difference 
    //! between the reference state at Tr, Pr and T,P
    /*!
     *  This is eEqn. 61 in Johnson et al. (1992). Actually, there appears to
     *  be an error in the latter. This is a correction.
     */
    double deltaS() const;


    double electrostatic_radii_calc();

 
    double ag(const double temp, const int ifunc = 0) const;
    double bg(const double temp, const int ifunc = 0) const;
    double g(const double temp, const double pres, const int ifunc = 0) const;

    //! Difference function f appearing in the formulation
    /*!
     * Function f appearing in the Johnson et al formulation of omega_j
     *   Eqn. 33 ref
     * 
     * @param temp      Temperature kelvin
     * @param pres      Pressure (pascal)
     * @param ifunc     parameters specifying the desired information
     *                 - 0 function value
     *                 - 1 derivative wrt temperature
     *                 - 2 2nd derivative wrt temperature
     *                 - 3 derivative wrt pressure
     */
    double f(const double temp, const double pres, const int ifunc = 0) const;
    double gstar(const double temp, const double pres, const int ifunc = 0) const;

    double LookupGe(const std::string& s);
    void convertDGFormation();

  private:
    //!  Water standard state calculator
    /*!
     *  derived from the equation of state for water.
     */
    PDSS_Water *m_waterSS;

    //! Current value of the pressure for this object
    mutable doublereal m_pres;

    //! density of standard-state water
    /*!
     * internal temporary variable
     */
    mutable double m_densWaterSS;

    /**
     *  Pointer to the water property calculator
     */
    WaterProps *m_waterProps;


    //! Born coefficient for the current ion or species

    doublereal m_born_coeff_j;

    //! Electrostatic radii
    doublereal m_r_e_j;


    //! Value of deltaG of Formation at Tr and Pr    (cal gmol-1)
    /*!
     *  Tr = 298.15   Pr = 1 atm
     *
     *  This is the delta G for the formation reaction of the
     *  ion from elements in their stable state at Tr, Pr.
     */
    doublereal m_deltaG_formation_tr_pr;

    //! Value of deltaH of Formation at Tr and Pr    (cal gmol-1)
    /*!
     *  Tr = 298.15   Pr = 1 atm
     *
     *  This is the delta H for the formation reaction of the
     *  ion from elements in their stable state at Tr, Pr.
     */
    doublereal m_deltaH_formation_tr_pr;

    //! Value of the Absolute Gibbs Free Energy NIST scale at tr and pr
    /*!
     *  this is the NIST scale value of Gibbs free energy at T_r = 298.15
     *  and P_r = 1 atm.
     *
     *  J kmol-1
     */
    doublereal m_Mu0_tr_pr;

    //! Value of S_j at Tr and Pr    (cal gmol-1 K-1)
    /*!
     *  Tr = 298.15   Pr = 1 atm
     */
    doublereal m_Entrop_tr_pr;

    //! a1 coefficient (cal gmol-1 bar-1)
    doublereal m_a1;

    //! a2 coefficient (cal gmol-1)
    doublereal m_a2;

    //! a3 coefficient (cal K gmol-1 bar-1)
    doublereal m_a3;

    //! a4 coefficient (cal K gmol-1)
    doublereal m_a4;

    //! c1 coefficient (cal gmol-1 K-1)
    doublereal m_c1;
    
    //! c2 coefficient (cal K gmol-1)
    doublereal m_c2;

    //! omega_pr_tr coefficient(cal gmol-1)
    doublereal m_omega_pr_tr;

    //! y = dZdT = 1/(esp*esp) desp/dT
    double m_Y_pr_tr;

  
    double m_Z_pr_tr;
 
    //! Reference pressure is 1 atm in units of bar= 1.0132
    doublereal m_presR_bar;

    //! small value that is not quite zero
    doublereal m_domega_jdT_prtr;

    //! Charge of the ion
    doublereal m_charge_j;

  };

}

#endif



