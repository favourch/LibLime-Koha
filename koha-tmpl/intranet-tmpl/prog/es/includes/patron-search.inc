
<h1 id="logo"><a href="/cgi-bin/koha/mainpage.pl"><!-- TMPL_VAR NAME="LibraryName" --></a></h1><!-- Begin Patrons Resident Search Box -->
<!-- TMPL_IF NAME="CAN_user_circulate" --><!-- TMPL_IF NAME="CircAutocompl" --><script type="text/javascript">
//<![CDATA[
YAHOO.util.Event.onContentReady("header_search", function() {
    new function() {
        // Define a custom formatter function
        this.fnCustomFormatter = function(oResultItem, sQuery) {
            var name        = oResultItem[0];
            var cardnumber  = oResultItem[1];
            var address     = oResultItem[2];
            var city        = oResultItem[3];
            var zip         = oResultItem[4];
            var aMarkup = [
                "<div class=\"sample-result\">",
                name,
                " (",
                cardnumber,
                ")<small> -- ",
                address,
                ", ",
                city,
                "<\/small>",
                "<\/div>"];
            return (aMarkup.join(""));
        };

        // Instantiate one XHR DataSource and define schema as an array:
        //     ["Record Delimiter",
        //     "Field Delimiter"]
        this.oACDS = new YAHOO.widget.DS_XHR("/cgi-bin/koha/circ/ysearch.pl", ["\n", "\t"]);
        this.oACDS.responseType = YAHOO.widget.DS_XHR.TYPE_FLAT;
        this.oACDS.maxCacheEntries = 60;
        this.oACDS.queryMatchSubset = true;
    
        // Instantiate first AutoComplete
        var myInput = document.getElementById('findborrower');
        var myContainer = document.getElementById('yborrowercontainer');
        this.oAutoComp = new YAHOO.widget.AutoComplete(myInput,myContainer,this.oACDS);
        //this.oAutoComp.delimChar = ";";
        //this.oAutoComp.queryDelay = 1;
        this.oAutoComp.formatResult = this.fnCustomFormatter;
}
});    
//]]>
</script><!-- /TMPL_IF --><!-- /TMPL_IF -->
<div id="header_search">
	<div id="patron_search" class="residentsearch">
		<p class="tip">Enter first and/or last name or card number for standard search. <br/>For email or phone, you may enter partial text with a * for truncation (e.g., myemail* or *111-2222).</p>
		<form action="/cgi-bin/koha/members/member.pl" method="post">
    			<input id="searchmember" class="focus" name="member" type="text" />
			<label for="searchfield">Search Fields:</label>
			<select name="searchfield" id="searchfield">
				<option value="">Standard</option>
				<option value="email">E-Mail</option>
				<option value="borrowernumber">Número de socio:</option>
				<option value="phonenumber">Phone Number</option>
			</select>
			<label for="orderby">Order By:</label>
			<select name="orderby" id="searchorderby">
				<option value="surname,firstname">Apellidos</option>
				<option value="cardnumber">N&uacute;mero de Carnet</option>
			</select>
			<input value="Buscar" class="submit" type="submit">
		</form>
	</div>

	<!-- TMPL_IF NAME="CAN_user_circulate" -->
		<div id="circ_search" class="residentsearch" style="display:none;">
			<p class="tip">Enter first and/or last name or card number for standard search. <br/>For email or phone, you may enter partial text with a * for truncation (e.g., myemail* or *111-2222).</p>
			<form action="/cgi-bin/koha/circ/circulation.pl" method="post">
				<!-- TMPL_IF NAME="CircAutocompl" -->
					<nobr>
						<div class="autocomplete">
							<div id="borrowerautocomplete" class="autocomplete">
								<input autocomplete="off" id="findborrower" name="findborrower" type="text" />
								<div id="yborrowercontainer"></div>
	
								<label for="searchfield">Search Fields:</label>
								<select name="searchfield" id="searchfield">
									<option value="">Standard</option>
									<option value="email">E-Mail</option>
									<option value="borrowernumber">Número de socio:</option>
									<option value="phonenumber">Phone Number</option>
								</select>
	
								<label for="orderby">Order By:</label>
								<select name="orderby" id="searchorderby">
									<option value="surname,firstname">Apellidos</option>
									<option value="cardnumber">N&uacute;mero de Carnet</option>
								</select>
	
								<input id="ysearchsubmit" type="submit" class="submit" value="Enviar">
								<input name="branch" value="<!-- TMPL_VAR name="branch" -->" type="hidden" />
								<input name="printer" value="" type="hidden" />
							</div>
						</div>
					</nobr>
				<!-- TMPL_ELSE -->
					<input id="findborrower" name="findborrower" size="40" type="text" />
					<input name="branch" value="<!-- TMPL_VAR name="branch" -->" type="hidden" />
					<input name="printer" value="" type="hidden" />
					<input value="Enviar" class="submit" type="submit">
				<!-- /TMPL_IF -->
			</form>
		</div>
	<!-- /TMPL_IF -->
	<!-- TMPL_IF NAME="CAN_user_catalogue" -->
	<div id="catalog_search" class="residentsearch" style="display:none;">
	<p class="tip">Ingrese palabaras clave para la búsqueda:</p>
		<form action="/cgi-bin/koha/catalogue/search.pl"  method="get" id="cat-search-block">
			 <input type="text" name="q" id="search-form" size="40" value="" title="Ingrese los t&eacute;rminos de b&uacute;squeda." class="form-text">
				<input type="submit" name="op" id="opac-submit" value="Enviar" class="submit">
		</form>
	</div><!-- /TMPL_IF -->
			<ul>
			<li><a href="/cgi-bin/koha/members/members-home.pl#patron_search">Buscar socios</a></li>
			<!-- TMPL_IF NAME="CAN_user_circulate" --><li><a href="/cgi-bin/koha/circ/circulation.pl#circ_search">Préstamo</a></li><!-- /TMPL_IF -->
			<!-- TMPL_IF NAME="CAN_user_catalogue" --><li><a href="/cgi-bin/koha/catalogue/search.pl#catalog_search">Buscar en el cat&aacute;logo</a></li><!-- /TMPL_IF -->
			</ul>	
</div>
<!-- End Patrons Resident Search Box -->